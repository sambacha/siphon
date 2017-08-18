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


#define MASK_INT(m) (*end & m)

#define MASK_BOOL(m) ((bool)MASK_INT(m))


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
		end++;
		if (p->as.lencode == SP_WS_EMPTY) YIELD (SP_WS_META, DONE);
		YIELD (SP_WS_META, LEN);

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
