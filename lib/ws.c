#include "../../include/siphon/ws.h"
#include "parser.h"

#include <assert.h>
#include <ctype.h>

/**
 * scanner states
 */

// frame metadata
// byte 1: FIN flag, 3 RSV flags and opcode
// byte 2: MASK flag, lencode

#define META           0x00000F
#define META_FIN       0x000001
#define META_RSV       0x000002
#define META_OPCODE    0x000003
#define META_MASK      0x000004
#define META_LENCODE   0x000005


// payload length
// byte 2 if lencode <= 125
// bytes 3-4 if lencode = 126
// bytes 3-10 if lencode = 127

// Note: LEN_8 should really be LEN_7 because of its max value is 127,
// but, it's kept LEN_8 for consistency with SP_WS_LEN_8, which in turn is
// consistent with its matching type, uint8_t.

#define LEN            0x0000F0
#define LEN_8          0x000010
#define LEN_16         0x000020
#define LEN_64         0x000030


// payload masking key
// bytes 3-6 if lencode <= 125
// bytes 5-8 if lencode = 126
// bytes 11-14 if lencode = 127

#define MASKING        0x000F00
#define MASKING_KEY    0x000100


/**
 * bit masks
 */

// manipulate first 2 bytes which contain frame metadata

#define FIN_MASK       0x80
#define RSV1_MASK      0x40
#define RSV2_MASK      0x20
#define RSV3_MASK      0x10
#define OPCODE_MASK    0xf
#define MASK_MASK      0x80
#define LENCODE_MASK   0x7f


/**
 * constants
 */

// length of the unencoded key in the Sec-WebSocket-Key header
#define WS_KEY_LEN     16

// maximum length of the payload of a control frame
#define CTRL_FRAME_MAX SP_WS_LEN_8

// number of bytes required to decode a 16-bit payload length
#define LEN_16_SIZE 2

// number of bytes required to decode a 64-bit payload length
#define LEN_64_SIZE 8

// number of bytes required to decode the masking key
#define MASKING_KEY_SIZE 4


/**
 * macros
 */

#define MASK_INT(msk) (*end & msk)

#define MASK_BOOL(msk) ((bool)MASK_INT(msk))

#define YIELD_LEN() do {                                 \
		if (p->client) YIELD (SP_WS_PAYLOAD_LEN, DONE);      \
		YIELD (SP_WS_PAYLOAD_LEN, MASKING);                  \
		} while (0)


#if BYTE_ORDER == LITTLE_ENDIAN

/**
 * Reads a 16-bit unsigned int
 * @dst: value to store the read value
 * @src: the read position of the buffer
 */
# define READ_UINT16(dst, src) do {          \
	uint16_t mem = *(uint16_t *)(src);         \
	(dst) = __builtin_bswap16 (mem);           \
} while (0)

/**
 * Reads a 64-bit unsigned int
 * @dst: value to store the read value
 * @src: the read position of the buffer
 */
# define READ_UINT64(dst, src) do {          \
	uint64_t mem = *(uint64_t *)(src);         \
	(dst) = __builtin_bswap64 (mem);           \
} while (0)

#elif BYTE_ORDER == BIG_ENDIAN

/**
 * Reads a 16-bit unsigned int
 * @dst: value to store the read value
 * @src: the read position of the buffer
 */
# define READ_UINT16(dst, src) do { \
	(dst) = (*(uint16_t *)(src));   \
} while (0)

/**
 * Reads a 64-bit unsigned int
 * @dst: value to store the read value
 * @src: the read position of the buffer
 */
# define READ_UINT64(dst, src) do { \
	(dst) = (*(uint64 *)(src));  \
} while (0)

#endif


static ssize_t
parse_meta (SpWs *restrict p, const uint8_t *const restrict m, const size_t len)
{
	EXPECT_SIZE(2, false, SP_WS_ESYNTAX);

	const uint8_t *end = m + p->off;

	p->type = SP_WS_NONE;

	switch (p->cs) {
	case META:
		p->cs = META_FIN;

	case META_FIN:
		p->as.fin = MASK_BOOL (FIN_MASK);
		p->cs = META_RSV;

	case META_RSV:
		p->as.rsv1 = MASK_BOOL (RSV1_MASK);
		p->as.rsv2 = MASK_BOOL (RSV2_MASK);
		p->as.rsv3 = MASK_BOOL (RSV3_MASK);
		p->cs = META_OPCODE;

	case META_OPCODE:
		p->as.opcode = MASK_INT (OPCODE_MASK);
		p->cs = META_MASK;
		end++;

	case META_MASK:
		p->as.mask = MASK_BOOL (MASK_MASK);
		p->cs = META_LENCODE;

	case META_LENCODE:
		p->as.lencode = MASK_INT (LENCODE_MASK);
		if (p->as.lencode && p->as.lencode <= SP_WS_LEN_8)
		{
			p->as.len.u8 = p->as.lencode;
			p->as.lencode = SP_WS_LEN_8;
		}
		end++;
		if (p->as.lencode == SP_WS_EMPTY) YIELD (SP_WS_META, DONE);
		YIELD (SP_WS_META, LEN);

	default:
		YIELD_ERROR (SP_WS_ESTATE);
	}
}

static ssize_t
parse_len (SpWs *restrict p, const uint8_t *const restrict m, const size_t len)
{
	const uint8_t *end = m + p->off;

	p->type = SP_WS_NONE;

	switch (p->cs) {
	case LEN:
		p->cs = LEN_8;

	case LEN_8:
		if (p->as.lencode == SP_WS_LEN_8)
		{
			YIELD_LEN ();
		}
		p->cs = LEN_16;

	case LEN_16:
		if (p->as.lencode == SP_WS_LEN_16)
		{
			EXPECT_SIZE (LEN_16_SIZE, false, SP_WS_ESYNTAX);
			READ_UINT16 (p->as.len.u16, m);
			end += LEN_16_SIZE;
			YIELD_LEN ();
		}
		p->cs = LEN_64;

	case LEN_64:
		if (p->as.lencode == SP_WS_LEN_64)
		{
			EXPECT_SIZE (LEN_64_SIZE, false, SP_WS_ESYNTAX);
			READ_UINT64 (p->as.len.u64, m);
			end += LEN_64_SIZE;
			YIELD_LEN ();
		}
		YIELD_ERROR (SP_WS_ESTATE);

	default:
		YIELD_ERROR (SP_WS_ESTATE);
	}
}


static ssize_t
parse_masking_key (SpWs *restrict p, const uint8_t *const restrict m, const size_t len)
{
	const uint8_t *end = m + p->off;

	p->type = SP_WS_NONE;

	switch (p->cs) {
	case MASKING:
		p->cs = MASKING_KEY;

	case MASKING_KEY:
		EXPECT_SIZE (MASKING_KEY_SIZE, false, SP_WS_ESYNTAX);
		memcpy(p->as.masking_key, end, MASKING_KEY_SIZE);
		end += MASKING_KEY_SIZE;
		YIELD (SP_WS_MASKING_KEY, DONE);

	default:
		YIELD_ERROR (SP_WS_ESTATE);
	}
}

int
sp_ws_init_client (SpWs *p)
{
	assert (p != NULL);

	memset (p, 0, sizeof *p);
	p->cs = META;
	p->client = true;
	return 0;
}

int
sp_ws_init_server (SpWs *p)
{
	assert (p != NULL);

	memset (p, 0, sizeof *p);
	p->cs = META;
	p->client = false;
	return 0;
}

void
sp_ws_reset (SpWs *p)
{
	assert (p != NULL);

	if (p->client) {
		sp_ws_init_client (p);
		return;
	}
	sp_ws_init_server (p);
}

ssize_t
sp_ws_next (SpWs *p, const void *restrict buf, size_t len)
{
	assert (p != NULL);

	if (len == 0) {
		return 0;
	}

	ssize_t rc;
	p->scans++;
	p->cscans++;

	if (p->cs & META) rc = parse_meta (p, buf, len);
	else if (p->cs & LEN) rc = parse_len (p, buf, len);
	else if (p->cs & MASKING) rc = parse_masking_key (p, buf, len);
	else { YIELD_ERROR (SP_WS_ESTATE); }
	if (rc > 0) {
		p->cscans = 0;
	}
	else if (rc == 0 && p->cscans > 64) {
		YIELD_ERROR (SP_WS_ETOOSHORT);
	}
	return rc;
}

bool
sp_ws_is_done (const SpWs *p)
{
	assert (p != NULL);

	return IS_DONE (p->cs);
}

size_t
sp_ws_mask (void *dst, const void *restrict src, size_t len, uint8_t *key)
{
	/**
	 * The same algorithm applies regardless of the direction of the
	 * translation, i.e., the same steps are applied to mask the payload and
	 * unmask the payload
	 */
	const uint8_t *s = src;
	uint8_t *d = dst;

	size_t n, j;
	for (n = 0; n < len; n++) {
		j = n % 4;
		d[n] = *s ^ key[j];
		s++;
	}

	return n;
}
