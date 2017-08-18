#include "../include/siphon/ws.h"
#include "../include/siphon/alloc.h"
#include "../include/siphon/error.h"
#include "../include/siphon/fmt.h"
#include "mu.h"

#include <stdlib.h>
#include <ctype.h>

typedef struct {
	size_t len;
	char payload[256];
} Message;


static bool
parse (SpWs *p, Message *msg, const uint8_t *in, size_t inlen, ssize_t speed)
{
	memset (msg, 0, sizeof *msg);

	const uint8_t *buf = in;
	size_t len, trim = 0;
	ssize_t rc;
	bool ok = true;

	if (speed > 0) {
		len = speed;
	}
	else {
		len = inlen;
	}

	while (!sp_ws_is_done (p)) {
		mu_assert_uint_ge (len, trim);
		if (len < trim) {
			ok = false;
			goto out;
		}

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

		if (p->type == SP_WS_PAYLOAD_LEN) {
			if (p->as.lencode == SP_WS_LEN_8) {
				msg->len = (size_t)p->as.len.u8;
			} else if (p->as.lencode == SP_WS_LEN_16) {
				msg->len = (size_t)p->as.len.u16;
			} else if (p->as.lencode == SP_WS_LEN_64) {
				msg->len = (size_t)p->as.len.u64;
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
test_server_decode_meta (ssize_t speed)
{
	SpWs p;
	sp_ws_init_server (&p);

	static const uint8_t frame[] = {0xd9, 0x0};

	Message msg;
	mu_fassert (parse (&p, &msg, frame, sizeof frame, speed));

	mu_assert (p.as.fin);
	mu_assert (p.as.rsv1);
	mu_assert (!p.as.rsv2);
	mu_assert (p.as.rsv3);
	mu_assert_int_eq (SP_WS_PING, p.as.opcode);
	mu_assert (!p.as.mask);
	mu_assert_int_eq (SP_WS_EMPTY, p.as.lencode);
}

static void
test_client_decode_meta (ssize_t speed)
{
	SpWs p;
	sp_ws_init_client (&p);

	static const uint8_t frame[] = {0x28, 0x80};

	Message msg;
	mu_fassert (parse (&p, &msg, frame, sizeof frame, speed));

	mu_assert (!p.as.fin);
	mu_assert (!p.as.rsv1);
	mu_assert (p.as.rsv2);
	mu_assert (!p.as.rsv3);
	mu_assert_int_eq (SP_WS_CLOSE, p.as.opcode);
	mu_assert (p.as.mask);
	mu_assert_int_eq (SP_WS_EMPTY, p.as.lencode);
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
		test_server_decode_meta (i);
		test_client_decode_meta (i);
	}

	mu_assert (sp_alloc_summary ());
}
