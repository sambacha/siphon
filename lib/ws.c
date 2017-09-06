#include "../../include/siphon/ws.h"
#include "../../include/siphon/endian.h"
#include "parser.h"

#include <assert.h>
#include <ctype.h>

/**
 * scanner states
 */

// frame metadata
// byte 1: FIN flag, 3 RSV flags and opcode
// byte 2: MASK flag, paylen

#define META           0x00000F
#define META_FIN       0x000001
#define META_RSV       0x000002
#define META_OPCODE    0x000003
#define META_MASK      0x000004
#define META_PAYLEN    0x000005


// payload length
// byte 2     if 0 <= byte 2 <= 125
// bytes 3-4  if byte 2 == 126
// bytes 3-10 if byte 2 == 127

#define LEN            0x0000F0
#define LEN_7          0x000010
#define LEN_16         0x000020
#define LEN_64         0x000030


// payload masking key
// bytes 3-6   if 0 <= byte 2 <= 125
// bytes 5-8   if byte 2 == 126
// bytes 11-14 if byte 2 == 127

#define MASK           0x000F00
#define MASK_KEY       0x000100


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
#define PAYLEN_MASK    0x7f


/**
 * constants
 */

#define LEN_16_BYTES   2
#define LEN_64_BYTES   8
#define MASK_KEY_BYTES 4

#define LEN_7_CODE     125
#define LEN_16_CODE    126
#define LEN_64_CODE    127

#define CTRL_LEN_MAX   LEN_7_CODE


/**
 * macros
 */

#define MASK_INT(msk) (*end & msk)

#define MASK_BOOL(msk) ((bool)MASK_INT(msk))

#define YIELD_LEN() do {                             \
if (p->client) YIELD (SP_WS_PAYLEN, DONE);           \
		YIELD (SP_WS_PAYLEN, MASK);                      \
} while (0)


/**
 * Reads a 16-bit unsigned int
 * @dst: value to store the read value
 * @src: the read position of the buffer
 */
# define READ_UINT16(dst, src) do {                  \
	uint16_t out = 0;                                  \
	memcpy (&out, src, sizeof out);                    \
	(dst) = sp_be16toh (out);                          \
} while (0)

/**
 * Reads a 64-bit unsigned int
 * @dst: value to store the read value
 * @src: the read position of the buffer
 */
# define READ_UINT64(dst, src) do {                  \
	uint64_t out = 0;                                  \
	memcpy (&out, src, sizeof out);                    \
	(dst) = sp_be64toh (out);                          \
} while (0)


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
		p->as.masked = MASK_BOOL (MASK_MASK);
		p->cs = META_PAYLEN;

	case META_PAYLEN:
		p->as.paylen.type = SP_WS_LEN_NONE;
		p->as.paylen.len.u7 = MASK_INT (PAYLEN_MASK);
		end++;
		if (!p->as.paylen.len.u7) YIELD (SP_WS_META, DONE);
		YIELD (SP_WS_META, LEN);

	default:
		YIELD_ERROR (SP_WS_ESTATE);
	}
}

static ssize_t
parse_paylen (SpWs *restrict p, const uint8_t *const restrict m, const size_t len)
{
	const uint8_t *end = m + p->off;

	p->type = SP_WS_NONE;

	switch (p->cs) {
	case LEN:
		p->cs = LEN_7;

	case LEN_7:
		if (p->as.paylen.len.u7 <= LEN_7_CODE)
		{
			p->as.paylen.type = SP_WS_LEN_7;
			YIELD_LEN ();
		}
		p->cs = LEN_16;

	case LEN_16:
		if (p->as.paylen.len.u7 == LEN_16_CODE)
		{
			EXPECT_SIZE (LEN_16_BYTES, false, SP_WS_ESYNTAX);
			p->as.paylen.type = SP_WS_LEN_16;
			READ_UINT16 (p->as.paylen.len.u16, m);
			end += LEN_16_BYTES;
			YIELD_LEN ();
		}
		p->cs = LEN_64;

	case LEN_64:
		if (p->as.paylen.len.u7 == LEN_64_CODE)
		{
			EXPECT_SIZE (LEN_64_BYTES, false, SP_WS_ESYNTAX);
			p->as.paylen.type = SP_WS_LEN_64;
			READ_UINT64 (p->as.paylen.len.u64, m);
			end += LEN_64_BYTES;
			YIELD_LEN ();
		}
		YIELD_ERROR (SP_WS_ESTATE);

	default:
		YIELD_ERROR (SP_WS_ESTATE);
	}
}


static ssize_t
parse_mask_key (SpWs *restrict p, const uint8_t *const restrict m, const size_t len)
{
	const uint8_t *end = m + p->off;

	p->type = SP_WS_NONE;

	switch (p->cs) {
	case MASK:
		p->cs = MASK_KEY;

	case MASK_KEY:
		EXPECT_SIZE (MASK_KEY_BYTES, false, SP_WS_ESYNTAX);
		memcpy(p->as.mask_key, end, MASK_KEY_BYTES);
		end += MASK_KEY_BYTES;
		YIELD (SP_WS_MASK_KEY, DONE);

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
	else if (p->cs & LEN) rc = parse_paylen (p, buf, len);
	else if (p->cs & MASK) rc = parse_mask_key (p, buf, len);
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

ssize_t
sp_ws_enc_frame (void *m, const SpWsFrame *restrict f)
{
	uint8_t *end = m;
	uint8_t meta = 0;

	if (f->fin) meta = FIN_MASK | meta;
	if (f->rsv1) meta = RSV1_MASK | meta;
	if (f->rsv2) meta = RSV2_MASK | meta;
	if (f->rsv3) meta = RSV3_MASK | meta;
	meta = f->opcode | meta;
	*(uint8_t *)end = meta;
	end++;

	meta = 0;
	if (f->paylen.type == SP_WS_LEN_7) meta = f->paylen.len.u7 & PAYLEN_MASK;
	if (f->paylen.type == SP_WS_LEN_16) meta = LEN_16_CODE & PAYLEN_MASK;
	if (f->paylen.type == SP_WS_LEN_64) meta = LEN_64_CODE & PAYLEN_MASK;
	if (f->masked) meta = MASK_MASK | meta;
	*(uint8_t *)end = meta;
	end++;

	if (f->paylen.type == SP_WS_LEN_16) {
		uint16_t len16 = sp_htobe16(f->paylen.len.u16);
		memcpy(end, &len16, LEN_16_BYTES);
		end += LEN_16_BYTES;
	}
	if (f->paylen.type == SP_WS_LEN_64) {
		uint64_t len64 = sp_htobe64(f->paylen.len.u64);
		memcpy(end, &len64, LEN_64_BYTES);
		end += LEN_64_BYTES;
	}

	if (f->masked) {
		memcpy(end, f->mask_key, MASK_KEY_BYTES);
		end += MASK_KEY_BYTES;
	}

	return end - (uint8_t*)m;
}

ssize_t
sp_ws_enc_ctrl (void *m, const SpWsCtrlOpcode code, const size_t len, const
uint8_t *key)
{
	SpWsFrame f;
	memset(&f, 0, sizeof f);

	f.fin = true;
	f.opcode = code;

	if (len) {
		if (len > CTRL_LEN_MAX) return SP_WS_ECTRLMAX;
		f.paylen.type = SP_WS_LEN_7;
		f.paylen.len.u7 = len;
	}

	if (key) {
		f.masked = (bool)key;
		memcpy(f.mask_key, key, MASK_KEY_BYTES);
	}

	return sp_ws_enc_frame (m, &f);
}

ssize_t
sp_ws_enc_ping (void *m, const uint8_t *key)
{
	return sp_ws_enc_ctrl (m, SP_WS_PING, 0, key);
}

ssize_t
sp_ws_enc_pong (void *m, const uint8_t *key)
{
	return sp_ws_enc_ctrl (m, SP_WS_PONG, 0, key);
}
