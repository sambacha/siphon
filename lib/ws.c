#include "../../include/siphon/ws.h"
#include "../../include/siphon/endian.h"
#include "parser.h"

#include <stdlib.h>
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

#define META_BYTES   2
#define LEN_16_BYTES   2
#define LEN_64_BYTES   8
#define MASK_KEY_BYTES 4
#define STATUS_BYTES   2

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
	if (p->as.masked) YIELD (SP_WS_PAYLEN, MASK);      \
	YIELD (SP_WS_PAYLEN, DONE);                        \
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
	EXPECT_SIZE(META_BYTES, false, SP_WS_ESYNTAX);

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
		uint8_t len = MASK_INT (PAYLEN_MASK);
		p->as.paylen.len.u7 = len;
		if (len > 0 && len <= LEN_7_CODE) p->as.paylen.type = SP_WS_LEN_7;
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
		if (p->as.paylen.len.u7 <= LEN_7_CODE) YIELD_LEN ();
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
sp_ws_init (SpWs *p)
{
	assert (p != NULL);

	memset (p, 0, sizeof *p);
	p->type = SP_WS_NONE;
	p->cs = META;
	return 0;
}

void
sp_ws_reset (SpWs *p)
{
	assert (p != NULL);

	sp_ws_init (p);
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
sp_ws_mask (void *dst, const void *restrict src, size_t len, const uint8_t *key)
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
sp_ws_enc_frame (void *buf, const SpWsFrame *f)
{
	uint8_t *end = buf;
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

	return end - (uint8_t*)buf;
}

ssize_t
sp_ws_enc_ctrl (void *buf, const SpWsCtrlOpcode code, size_t len, const uint8_t *key)
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

	return sp_ws_enc_frame (buf, &f);
}

ssize_t
sp_ws_enc_ping (void *buf, size_t len, const uint8_t *key)
{
	return sp_ws_enc_ctrl (buf, SP_WS_PING, len, key);
}

ssize_t
sp_ws_enc_pong (void *buf, size_t len, const uint8_t *key)
{
	return sp_ws_enc_ctrl (buf, SP_WS_PONG, len, key);
}

ssize_t
sp_ws_enc_close (void *buf, SpWsStatus stat, size_t len, const uint8_t *key)
{
	uint8_t *end = buf;

	if (stat <= SP_WS_STATUS_NONE)
		return sp_ws_enc_ctrl (buf, SP_WS_CLOSE, 0, NULL);

	ssize_t rc = sp_ws_enc_ctrl (buf, SP_WS_CLOSE, len+STATUS_BYTES, key);
	if (rc <= 0) return rc;
	end += rc;

	*(uint16_t *)end = sp_htobe16 (stat);
	end += STATUS_BYTES;

	return end - (uint8_t*)buf;
}

ssize_t
sp_ws_meta_length (const SpWs *p)
{
	assert (p != NULL);

	if (p->type < SP_WS_META) return SP_WS_ESTATE;

	uint16_t len = 2;
	if (p->as.paylen.type == SP_WS_LEN_16)
		len += LEN_16_BYTES;
	if (p->as.paylen.type == SP_WS_LEN_64)
		len += LEN_64_BYTES;
	if (p->as.masked)
		len += MASK_KEY_BYTES;

	return len;
}

ssize_t
sp_ws_payload_length (const SpWs *p, uint64_t *len)
{
	assert (p != NULL);

	if (p->type < SP_WS_PAYLEN) return SP_WS_ESTATE;

	switch (p->as.paylen.type) {
	case SP_WS_LEN_7: (*len) = (uint64_t) p->as.paylen.len.u7; break;
	case SP_WS_LEN_16: (*len) = (uint64_t) p->as.paylen.len.u16; break;
	case SP_WS_LEN_64:  (*len) = (uint64_t) p->as.paylen.len.u64; break;
	default:  (*len) = 0;
	}

	return 0;
}

static char*
bool_string (bool v)
{
	return v ? "true"  : "false";
}

static void
print_paylen (const SpWs *p, FILE *out)
{
	assert (p != NULL);

	SpWsLenType type = p->as.paylen.type;
	if (type == SP_WS_LEN_NONE || type == SP_WS_LEN_7) return;

	fprintf (out, "    paylen   = { type: ");
	switch (type) {
	case SP_WS_LEN_16:
		fprintf (out, "16-bit, value: %d", p->as.paylen.len.u16);
		break;
	case SP_WS_LEN_64:
		fprintf (out, "64-bit, value: %" PRIu64, p->as.paylen.len.u64);
		break;
	default: break;
	}
	fprintf (out, " }\n");
}

static void
print_meta (const SpWs *p, FILE *out)
{
	assert (p != NULL);

	fprintf (out, "    fin      = %s\n", bool_string(p->as.fin));
	fprintf (out, "    rsv1     = %s\n", bool_string(p->as.rsv1));
	fprintf (out, "    rsv2     = %s\n", bool_string(p->as.rsv2));
	fprintf (out, "    rsv3     = %s\n", bool_string(p->as.rsv3));
	fprintf (out, "    opcode   = ");
	switch ((int)p->as.opcode) {
	case SP_WS_CONT:  fprintf (out, "CONT");  break;
	case SP_WS_TEXT:  fprintf (out, "TEXT");  break;
	case SP_WS_BIN:   fprintf (out, "BIN");   break;
	case SP_WS_CLOSE: fprintf (out, "CLOSE"); break;
	case SP_WS_PING:  fprintf (out, "PING");  break;
	case SP_WS_PONG:  fprintf (out, "PONG");  break;
	default:          fprintf (out, "UNKNOWN");
	}
	fprintf (out, "\n");
	fprintf (out, "    mask     = %s\n", bool_string(p->as.masked));
	if (p->as.paylen.type == SP_WS_LEN_7)
		fprintf (out, "    paylen   = { type: 7-bit, value: %d }\n", p->as.paylen.len.u7);
}

static void
print_mask_key (const SpWs *p, FILE *out)
{
	assert (p != NULL);

	if (p->as.masked) {
		fprintf (out, "    mask key = [");
		for (size_t i = 0; i < MASK_KEY_BYTES; i++)
			fprintf (out, "0x%x%s", p->as.mask_key[i], (i < MASK_KEY_BYTES - 1 ? ", "  : ""));
		fprintf (out, "]\n");
	}
}

void
sp_ws_print_meta (const SpWs *p, const void *restrict buf, FILE *out)
{
	if (out == NULL) {
		out = stderr;
	}
	flockfile (out);

	if (p == NULL) {
		fprintf (out, "#<SpWs:(null)>\n");
		funlockfile (out);
		return;
	}

	const uint8_t *end = buf;
	size_t len = 0, i = 0;

	fprintf (out, "#<SpWs:%p", (void *)p);
	fprintf (out, " value=[");
	if (p->type == SP_WS_META) len = META_BYTES;
	if (p->type == SP_WS_PAYLEN) len = sp_ws_meta_length (p) - META_BYTES;
	if (p->type == SP_WS_MASK_KEY) len = MASK_KEY_BYTES;
	for (i = 0; i < len; i++)
		fprintf (out, "0x%x%s", *end++, (i < len - 1 ? ", "  : ""));
	fprintf (out, "]> {\n");

	if (p->type == SP_WS_META) print_meta (p, out);
	if (p->type == SP_WS_PAYLEN) print_paylen (p, out);
	if (p->type == SP_WS_MASK_KEY) print_mask_key (p, out);

	fprintf (out, "}\n");

	funlockfile (out);
}

void
sp_ws_print_payload (const SpWs *p, const void *restrict buf, FILE *out)
{
	// TODO this will not work for large payload

	assert (p != NULL);

	if (out == NULL) {
		out = stderr;
	}
	flockfile (out);

	const uint8_t *end = buf;
	uint64_t len;

	if (!sp_ws_is_done (p) || sp_ws_payload_length (p, &len) < 0) return;

	end += sp_ws_meta_length (p);
	char msg[len];
	if (p->as.masked) {
		sp_ws_mask (msg, end, len, p->as.mask_key);
	} else {
		strncat (msg, (char *)end, len);
	}
	fprintf (out, "%s\n", msg);

	funlockfile (out);
}

const char *
sp_ws_status_string (SpWsStatus stat)
{
	/**
	 * Text as added to the IANA registry.
	 * https://tools.ietf.org/html/rfc6455#section-11.7
	 */
	switch (stat) {
	case SP_WS_STATUS_NORMAL: return "Normal Closure";
	case SP_WS_STATUS_AWAY:   return "Going Away";
	case SP_WS_STATUS_PROTO:  return "Protocol error";
	case SP_WS_STATUS_TYPE:   return "Unsupported Data";
	case SP_WS_STATUS_DATA:   return "Invalid frame payload data";
	case SP_WS_STATUS_POLICY: return "Policy Violation";
	case SP_WS_STATUS_BIG:    return "Message Too Big";
	case SP_WS_STATUS_EXT:    return "Mandatory Ext.";
	case SP_WS_STATUS_FAIL:   return "Internal Server Error";
	default:                  return NULL;
	};
}
