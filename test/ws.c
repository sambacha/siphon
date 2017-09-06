#include "../include/siphon/ws.h"
#include "../include/siphon/alloc.h"
#include "../include/siphon/error.h"
#include "../include/siphon/fmt.h"
#include "mu.h"

#include <stdlib.h>
#include <ctype.h>


static void
repeat_char(char *buf, char c, size_t n)
{
	memset(buf, (int)c, n);
	buf[n] = '\0';
}

static bool
parse (SpWs *p, char *msg, const uint8_t *in, size_t inlen, ssize_t speed)
{
	if (msg) memset (msg, 0, sizeof *msg);

	const uint8_t *buf = in;
	size_t len, trim = 0;
	size_t payload = 0;
	ssize_t rc;
	bool ok = true;

	if (speed > 0) {
		len = speed;
	}
	else {
		len = inlen;
	}

	while (payload > 0 || !sp_ws_is_done (p)) {
		mu_assert_uint_ge (len, trim);
		if (len < trim) {
			ok = false;
			goto out;
		}

		if (payload > 0) {
			rc = len - trim;
			if (payload < (size_t)rc) {
				rc = payload;
			}
			strncat (msg, (char *)buf, rc);
			payload -= rc;
		}
		else {
			rc = sp_ws_next (p, buf, len - trim);

			// normally rc could equal 0 if a full scan couldn't be completed
			mu_assert_int_ge (rc, 0);
			if (rc < 0) {
				char err[256];
				sp_error_string (rc, err, sizeof err);
				fprintf (stderr, "Parsing Failed:\n\terror=\"%s\"\n\tinput=", err);
				sp_fmt_str (stderr, buf, len - trim, true);
				fprintf  (stderr, "\n");
				ok = false;
				goto out;
			}

			if ((p->client && p->type == SP_WS_PAYLEN) ||
					(!p->client && p->type == SP_WS_MASK_KEY)) {
				if (p->as.paylen.type == SP_WS_LEN_7) {
					payload = (size_t)p->as.paylen.len.u7;
				} else if (p->as.paylen.type == SP_WS_LEN_16) {
					payload = (size_t)p->as.paylen.len.u16;
				} else if (p->as.paylen.type == SP_WS_LEN_64) {
					// TODO support 64-bit payload lengths
				}
			}
		}


		// trim the buffer
		buf += rc;
		trim += rc;

		if (speed > 0) {
			len += speed;
			if (len > inlen) {
				len = inlen;
			}
		}
	}

out:
	return ok;
}

static void
test_parse_meta (ssize_t speed)
{
	SpWs p;
	sp_ws_init_client (&p);

	static const uint8_t frame[] = {0xd9, 0x0};

	mu_fassert (parse (&p, NULL, frame, sizeof frame, speed));

	mu_assert (p.as.fin);
	mu_assert (p.as.rsv1);
	mu_assert (!p.as.rsv2);
	mu_assert (p.as.rsv3);
	mu_assert_int_eq (SP_WS_PING, p.as.opcode);
	mu_assert (!p.as.masked);
	mu_assert_int_eq (0, p.as.paylen.len.u7);
}

static void
test_parse_paylen_8 (ssize_t speed)
{
	SpWs p;
	sp_ws_init_client (&p);

	static const uint8_t frame[] = {
		0x0, 0xb, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c,
		0x64
	};

	char msg[256];
	mu_fassert (parse (&p, msg, frame, sizeof frame, speed));

	mu_assert_int_eq (SP_WS_LEN_7, p.as.paylen.type);
	mu_assert_int_eq (11, p.as.paylen.len.u7);
	mu_assert_str_eq ("Hello World", msg);
}

static void
test_parse_paylen_16 (ssize_t speed)
{
	SpWs p;
	sp_ws_init_client (&p);

	size_t n = 0x3e8;
	size_t m = 0x4;
	char msg[n];
	char cmp[n];
	uint8_t frame[m+n];
	static const uint8_t meta[] = {0x0, 0x7e, 0x03, 0xe8};

	memmove (frame, meta, m);
	repeat_char ((char *)(frame+m), 's', n);
	repeat_char (cmp, 's', n);

	mu_fassert (parse (&p, msg, frame, sizeof frame, speed));

	mu_assert_int_eq (SP_WS_LEN_16, p.as.paylen.type);
	mu_assert_int_eq (n, p.as.paylen.len.u16);
	mu_assert_str_eq (cmp, msg);
}

static void
test_parse_mask_key ()
{
	SpWs p;
	sp_ws_init_server (&p);

	static const uint8_t f[] = {
		0x0, 0x8b, 0x55, 0x7f, 0x90, 0x4a, 0x1d, 0x1a, 0xfc, 0x26, 0x3a, 0x5f,
		0xc7, 0x25, 0x27, 0x13, 0xf4
	};

	char m[256];
	mu_fassert (parse (&p, m, f, sizeof f, 0));

	mu_assert_int_eq (0x55, p.as.mask_key[0]);
	mu_assert_int_eq (0x7f, p.as.mask_key[1]);
	mu_assert_int_eq (0x90, p.as.mask_key[2]);
	mu_assert_int_eq (0x4a, p.as.mask_key[3]);
}

static void
test_mask ()
{
	SpWs p;
	sp_ws_init_server (&p);

	static const uint8_t f[] = {
		0x0, 0x8b, 0x55, 0x7f, 0x90, 0x4a, 0x1d, 0x1a, 0xfc, 0x26, 0x3a, 0x5f,
		0xc7, 0x25, 0x27, 0x13, 0xf4
	};

	char m[256];
	mu_fassert (parse (&p, m, f, sizeof f, 0));

	char d[256];
	mu_assert_int_eq (11, sp_ws_mask (d, m, p.as.paylen.len.u7, p.as.mask_key));
	mu_assert_str_eq ("Hello World", d);
}

static void
test_enc_frame_meta ()
{
	SpWsFrame f = {
		.fin = true,
		.rsv1 = true,
		.rsv3 = true,
		.opcode = SP_WS_PING,
	};

	uint8_t m[16];
	mu_assert_int_eq (2, sp_ws_enc_frame (m, &f));
	mu_assert_int_eq (0xd9, m[0]);
	mu_assert_int_eq (0x0, m[1]);
}

static void
test_enc_frame_paylen_8 ()
{
	SpWsFrame f = {
		.paylen = {.type = SP_WS_LEN_7, .len.u7 = 11},
	};

	uint8_t m[16];
	mu_assert_int_eq (2, sp_ws_enc_frame (m, &f));
	mu_assert_int_eq (0x0, m[0]);
	mu_assert_int_eq (0x0b, m[1]);
}

static void
test_enc_frame_paylen_16 ()
{
	SpWsFrame f = {
		.paylen = {.type = SP_WS_LEN_16, .len.u16 = 0x3e8},
	};

	uint8_t m[16];
	mu_assert_int_eq (4, sp_ws_enc_frame (m, &f));
	mu_assert_int_eq (0x0, m[0]);
	mu_assert_int_eq (0x7e, m[1]);
	mu_assert_int_eq (0x03, m[2]);
	mu_assert_int_eq (0xe8, m[3]);
}

static void
test_enc_frame_mask_key ()
{
	SpWsFrame f = {
		.masked = true,
		.mask_key = "U\x7f\x90J",
	};

	uint8_t m[16];
	mu_assert_int_eq (6, sp_ws_enc_frame (m, &f));
	mu_assert_int_eq (0x55, m[2]);
	mu_assert_int_eq (0x7f, m[3]);
	mu_assert_int_eq (0x90, m[4]);
	mu_assert_int_eq (0x4a, m[5]);
}

static void
test_enc_ctrl ()
{
	uint8_t m[16];
	mu_assert_int_eq (2, sp_ws_enc_ctrl (m, SP_WS_PING, 0, NULL));
	mu_assert_int_eq (0x89, m[0]);
	mu_assert_int_eq (0x0, m[1]);
}

static void
test_enc_ctrl_masked ()
{
	uint8_t key[4] = {0x55, 0x7f, 0x90, 0x4a};

	uint8_t m[16];
	mu_assert_int_eq (6, sp_ws_enc_ctrl (m, SP_WS_PONG, 0, key));
	mu_assert_int_eq (0x8a, m[0]);
	mu_assert_int_eq (0x80, m[1]);
	mu_assert_int_eq (0x55, m[2]);
	mu_assert_int_eq (0x7f, m[3]);
	mu_assert_int_eq (0x90, m[4]);
	mu_assert_int_eq (0x4a, m[5]);
}

static void
test_enc_ctrl_len ()
{
	uint8_t m[16];
	mu_assert_int_eq (2, sp_ws_enc_ctrl (m, SP_WS_CLOSE, 11, NULL));
	mu_assert_int_eq (0x88, m[0]);
	mu_assert_int_eq (0xb, m[1]);
}

static void
test_enc_ctrl_len_max ()
{
	ssize_t rc = sp_ws_enc_ctrl (NULL, SP_WS_PONG, 126, NULL);
	mu_assert_int_eq (SP_WS_ECTRLMAX, rc);
}

static void
test_enc_ping ()
{
	uint8_t m[16];
	mu_assert_int_eq (2, sp_ws_enc_ping (m, NULL));
	mu_assert_int_eq (0x89, m[0]);
	mu_assert_int_eq (0x0, m[1]);
}

int
main (void)
{
	mu_init ("ws");

	/**
	 * Parse the input at varying "speeds". The speed is the number
	 * of bytes to emulate reading at each pass of the parser.
	 * 0 indicates that all bytes should be available at the start
	 * of the parser.
	 */
	for (ssize_t i = 0; i <= 250; i++) {
		test_parse_meta (i);
		test_parse_meta (i);
		test_parse_paylen_8 (i);
		test_parse_paylen_16 (i);
		// TODO test_parse_paylen_64
		test_parse_mask_key (i);
	}

	test_mask ();
	test_enc_frame_meta ();
	test_enc_frame_paylen_8 ();
	test_enc_frame_paylen_16 ();
	test_enc_frame_mask_key ();
	test_enc_ctrl ();
	test_enc_ctrl_masked ();
	test_enc_ctrl_len ();
	test_enc_ctrl_len_max ();
	test_enc_ping ();

	mu_assert (sp_alloc_summary ());
}
