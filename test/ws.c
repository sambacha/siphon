#include "../include/siphon/ws.h"
#include "../include/siphon/alloc.h"
#include "../include/siphon/error.h"
#include "../include/siphon/fmt.h"
#include "mu.h"

#include <ctype.h>
#include <stdlib.h>

static void repeat_char(char *buf, char c, size_t n) {
  memset(buf, (int)c, n);
  buf[n] = '\0';
}

static void cmp_ws_print(SpWs *p, const uint8_t *buf, char *fmt) {
  char *msg;
  char cmp[512];
  size_t len;
  FILE *out = open_memstream(&msg, &len);

  sp_ws_print_meta(p, buf, out);
  fclose(out);
  sprintf(cmp, fmt, (void *)p);
  mu_assert_str_eq(cmp, msg);
  free(msg);
}

static bool parse(SpWs *p, char *msg, const uint8_t *in, size_t inlen,
                  ssize_t speed) {
  if (msg)
    memset(msg, 0, sizeof *msg);

  const uint8_t *buf = in;
  size_t len, trim = 0;
  ssize_t rc;
  bool ok = true;

  if (speed > 0) {
    len = speed;
  } else {
    len = inlen;
  }

  while (!sp_ws_is_done(p)) {
    mu_assert_uint_ge(len, trim);
    if (len < trim) {
      ok = false;
      goto out;
    }

    rc = sp_ws_next(p, buf, len - trim);

    // normally rc could equal 0 if a full scan couldn't be completed
    mu_assert_int_ge(rc, 0);
    if (rc < 0) {
      char err[256];
      sp_error_string(rc, err, sizeof err);
      fprintf(stderr, "Parsing Failed:\n\terror=\"%s\"\n\tinput=", err);
      sp_fmt_str(stderr, buf, len - trim, true);
      fprintf(stderr, "\n");
      ok = false;
      goto out;
    }

    if (p->type == SP_WS_PAYLOAD) {
      if (!msg)
        break;
      if (p->as.masked) {
        char *m = (char *)malloc(rc);
        sp_ws_unmask(p, m, buf, rc);
        strncat(msg, m, rc);
        free(m);
      } else {
        strncat(msg, (char *)buf, rc);
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

static void test_parse_meta(ssize_t speed) {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t frame[] = {0xd9, 0x0};

  mu_fassert(parse(&p, NULL, frame, sizeof frame, speed));

  mu_assert(p.as.fin);
  mu_assert(p.as.rsv1);
  mu_assert(!p.as.rsv2);
  mu_assert(p.as.rsv3);
  mu_assert_int_eq(SP_WS_PING, p.as.opcode);
  mu_assert(!p.as.masked);
  mu_assert_int_eq(0, p.as.paylen.len.u7);
}

static void test_parse_paylen_7(ssize_t speed) {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t frame[] = {0x0,  0xb,  0x48, 0x65, 0x6c, 0x6c, 0x6f,
                                  0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64};

  char msg[256];
  mu_fassert(parse(&p, msg, frame, sizeof frame, speed));

  mu_assert_int_eq(SP_WS_LEN_7, p.as.paylen.type);
  mu_assert_int_eq(11, p.as.paylen.len.u7);
  mu_assert_str_eq("Hello World", msg);
}

static void test_parse_paylen_16(ssize_t speed) {
  SpWs p;
  sp_ws_init(&p);

  size_t n = 0x3e8;
  size_t m = 0x4;
  char msg[n];
  char cmp[n];
  uint8_t frame[m + n];
  static const uint8_t meta[] = {0x0, 0x7e, 0x03, 0xe8};

  memmove(frame, meta, m);
  repeat_char((char *)(frame + m), 's', n);
  repeat_char(cmp, 's', n);

  mu_fassert(parse(&p, msg, frame, sizeof frame, speed));

  mu_assert_int_eq(SP_WS_LEN_16, p.as.paylen.type);
  mu_assert_int_eq(n, p.as.paylen.len.u16);
  mu_assert_str_eq(cmp, msg);
}

static void test_parse_paylen_64(ssize_t speed) {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t frame[] = {0x0,  0x7f, 0x0,  0xff, 0xff, 0xff,
                                  0xff, 0xff, 0xff, 0xfe, 0x0};

  mu_fassert(parse(&p, NULL, frame, sizeof frame, speed));

  mu_assert_int_eq(SP_WS_LEN_64, p.as.paylen.type);
  mu_assert_int_eq(0xfffffffffffffe, p.as.paylen.len.u64);
}

static void test_parse_unmask(ssize_t speed) {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t f[] = {0x0,  0x8b, 0x55, 0x7f, 0x90, 0x4a,
                              0x1d, 0x1a, 0xfc, 0x26, 0x3a, 0x5f,
                              0xc7, 0x25, 0x27, 0x13, 0xf4};

  char m[256];
  mu_fassert(parse(&p, m, f, sizeof f, speed));

  mu_assert_int_eq(0x55, p.as.mask_key[0]);
  mu_assert_int_eq(0x7f, p.as.mask_key[1]);
  mu_assert_int_eq(0x90, p.as.mask_key[2]);
  mu_assert_int_eq(0x4a, p.as.mask_key[3]);
  mu_assert_str_eq("Hello World", m);
}

static void test_mask() {
  static const uint8_t k[] = {0x55, 0x7f, 0x90, 0x4a};
  static const uint8_t f[] = {0x1d, 0x1a, 0xfc, 0x26, 0x3a, 0x5f,
                              0xc7, 0x25, 0x27, 0x13, 0xf4};

  char d[256];
  memset(d, 0, sizeof d);
  mu_assert_int_eq(11, sp_ws_mask(d, f, 11, k));
  mu_assert_str_eq("Hello World", d);
}

static void test_unmask_max() {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t f[] = {0x0,  0x8b, 0x55, 0x7f, 0x90, 0x4a,
                              0x1d, 0x1a, 0xfc, 0x26, 0x3a, 0x5f,
                              0xc7, 0x25, 0x27, 0x13, 0xf4};

  mu_fassert(parse(&p, NULL, f, sizeof f, 0));
  mu_assert_int_eq(SP_WS_EUMASKMAX, sp_ws_unmask(&p, NULL, NULL, 12));
}

static void test_enc_frame_meta() {
  SpWsFrame f = {
      .fin = true,
      .rsv1 = true,
      .rsv3 = true,
      .opcode = SP_WS_PING,
  };

  uint8_t m[16];
  mu_assert_int_eq(2, sp_ws_enc_frame(m, &f));
  mu_assert_int_eq(0xd9, m[0]);
  mu_assert_int_eq(0x0, m[1]);
}

static void test_enc_frame_paylen_7() {
  SpWsFrame f = {
      .paylen = {.type = SP_WS_LEN_7, .len.u7 = 11},
  };

  uint8_t m[16];
  mu_assert_int_eq(2, sp_ws_enc_frame(m, &f));
  mu_assert_int_eq(0x0, m[0]);
  mu_assert_int_eq(0x0b, m[1]);
}

static void test_enc_frame_paylen_16() {
  SpWsFrame f = {
      .paylen = {.type = SP_WS_LEN_16, .len.u16 = 0x3e8},
  };

  uint8_t m[16];
  mu_assert_int_eq(4, sp_ws_enc_frame(m, &f));
  mu_assert_int_eq(0x0, m[0]);
  mu_assert_int_eq(0x7e, m[1]);
  mu_assert_int_eq(0x03, m[2]);
  mu_assert_int_eq(0xe8, m[3]);
}

static void test_enc_frame_paylen_64() {
  SpWsFrame f = {
      .paylen = {.type = SP_WS_LEN_64, .len.u64 = 0xfffffffffffffe},
  };

  uint8_t m[16];
  mu_assert_int_eq(10, sp_ws_enc_frame(m, &f));
  mu_assert_int_eq(0x0, m[0]);
  mu_assert_int_eq(0x7f, m[1]);
  mu_assert_int_eq(0x0, m[2]);
  mu_assert_int_eq(0xff, m[3]);
  mu_assert_int_eq(0xff, m[4]);
  mu_assert_int_eq(0xff, m[5]);
  mu_assert_int_eq(0xff, m[6]);
  mu_assert_int_eq(0xff, m[7]);
  mu_assert_int_eq(0xff, m[8]);
  mu_assert_int_eq(0xfe, m[9]);
}

static void test_enc_frame_paylen_max() {
  SpWsFrame f = {
      .paylen = {.type = SP_WS_LEN_64, .len.u64 = 0x0fffffffffffffff + 1},
  };

  uint8_t m[16];
  mu_assert_int_eq(SP_WS_ELENMAX, sp_ws_enc_frame(m, &f));
}

static void test_enc_frame_mask_key() {
  SpWsFrame f = {
      .masked = true,
      .mask_key = {0x55, 0x7f, 0x90, 0x4a},
  };

  uint8_t m[16];
  mu_assert_int_eq(6, sp_ws_enc_frame(m, &f));
  mu_assert_int_eq(0x0, m[0]);
  mu_assert_int_eq(0x80, m[1]);
  mu_assert_int_eq(0x55, m[2]);
  mu_assert_int_eq(0x7f, m[3]);
  mu_assert_int_eq(0x90, m[4]);
  mu_assert_int_eq(0x4a, m[5]);
}

static void test_enc_ctrl() {
  uint8_t m[16];
  mu_assert_int_eq(2, sp_ws_enc_ctrl(m, SP_WS_PING, 0, NULL));
  mu_assert_int_eq(0x89, m[0]);
  mu_assert_int_eq(0x0, m[1]);
}

static void test_enc_ctrl_masked() {
  uint8_t key[4] = {0x55, 0x7f, 0x90, 0x4a};

  uint8_t m[16];
  mu_assert_int_eq(6, sp_ws_enc_ctrl(m, SP_WS_PONG, 0, key));
  mu_assert_int_eq(0x8a, m[0]);
  mu_assert_int_eq(0x80, m[1]);
  mu_assert_int_eq(0x55, m[2]);
  mu_assert_int_eq(0x7f, m[3]);
  mu_assert_int_eq(0x90, m[4]);
  mu_assert_int_eq(0x4a, m[5]);
}

static void test_enc_ctrl_len() {
  uint8_t m[16];
  mu_assert_int_eq(2, sp_ws_enc_ctrl(m, SP_WS_CLOSE, 11, NULL));
  mu_assert_int_eq(0x88, m[0]);
  mu_assert_int_eq(0xb, m[1]);
}

static void test_enc_ctrl_len_max() {
  ssize_t rc = sp_ws_enc_ctrl(NULL, SP_WS_PONG, 126, NULL);
  mu_assert_int_eq(SP_WS_ECTRLMAX, rc);
}

static void test_enc_ping() {
  uint8_t m[16];
  mu_assert_int_eq(2, sp_ws_enc_ping(m, 0, NULL));
  mu_assert_int_eq(0x89, m[0]);
  mu_assert_int_eq(0x0, m[1]);
}

static void test_enc_pong() {
  uint8_t m[16];
  mu_assert_int_eq(2, sp_ws_enc_pong(m, 0, NULL));
  mu_assert_int_eq(0x8a, m[0]);
  mu_assert_int_eq(0x0, m[1]);
}

static void test_enc_close() {
  uint8_t m[16];
  mu_assert_int_eq(2, sp_ws_enc_close(m, 0, 0, NULL));
  mu_assert_int_eq(0x88, m[0]);
  mu_assert_int_eq(0x0, m[1]);
}

static void test_enc_close_status() {
  uint8_t m[16];
  mu_assert_int_eq(6, sp_ws_enc_close(m, SP_WS_STATUS_AWAY, 10, NULL));
  mu_assert_int_eq(0x88, m[0]);
  mu_assert_int_eq(0x0e, m[1]);
  mu_assert_int_eq(0x03, m[2]);
  mu_assert_int_eq(0xe9, m[3]);
  mu_assert_int_eq(0x20, m[4]);
  mu_assert_int_eq(0x20, m[5]);
}

static void test_enc_close_status_mask() {
  uint8_t key[4] = {0x55, 0x7f, 0x90, 0x4a};

  uint8_t m[16];
  mu_assert_int_eq(10, sp_ws_enc_close(m, SP_WS_STATUS_AWAY, 10, key));
  mu_assert_int_eq(0x88, m[0]);
  mu_assert_int_eq(0x8e, m[1]);
  mu_assert_int_eq(0x55, m[2]);
  mu_assert_int_eq(0x7f, m[3]);
  mu_assert_int_eq(0x90, m[4]);
  mu_assert_int_eq(0x4a, m[5]);
  mu_assert_int_eq(0x56, m[6]);
  mu_assert_int_eq(0x96, m[7]);
  mu_assert_int_eq(0xb0, m[8]);
  mu_assert_int_eq(0x6a, m[9]);
}

static void test_print_meta() {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t f[] = {0xd9, 0xb};

  sp_ws_next(&p, f, 2);
  char *fmt = "#<SpWs:%p value=[0xd9, 0xb]> {\n"
              "    fin      = true\n"
              "    rsv1     = true\n"
              "    rsv2     = false\n"
              "    rsv3     = true\n"
              "    opcode   = PING\n"
              "    mask     = false\n"
              "    paylen   = { type: 7-bit, value: 11 }\n"
              "}\n";
  cmp_ws_print(&p, f, fmt);
}

static void test_print_meta_empty() {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t f[] = {0xd9, 0x8b};

  char *fmt = "#<SpWs:%p value=[]> {\n"
              "}\n";
  cmp_ws_print(&p, f, fmt);
}

static void test_print_meta_paylen() {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t f[] = {0x0, 0x7e, 0x03, 0xe8};

  sp_ws_next(&p, f, 2);
  sp_ws_next(&p, f + 2, 2);
  char *fmt = "#<SpWs:%p value=[0x3, 0xe8]> {\n"
              "    paylen   = { type: 16-bit, value: 1000 }\n"
              "}\n";
  cmp_ws_print(&p, f + 2, fmt);
}

static void test_print_meta_mask_key() {
  SpWs p;
  sp_ws_init(&p);

  static const uint8_t f[] = {0xd9, 0x8b, 0x55, 0x7f, 0x90, 0x4a};

  sp_ws_next(&p, f, 2);
  sp_ws_next(&p, f + 2, 4);

  char *fmt = "#<SpWs:%p value=[0x55, 0x7f, 0x90, 0x4a]> {\n"
              "    mask key = [0x55, 0x7f, 0x90, 0x4a]\n"
              "}\n";
  cmp_ws_print(&p, f + 2, fmt);
}

int main(void) {
  mu_init("ws");

  /**
   * Parse the input at varying "speeds". The speed is the number
   * of bytes to emulate reading at each pass of the parser.
   * 0 indicates that all bytes should be available at the start
   * of the parser.
   */
  for (ssize_t i = 0; i <= 250; i++) {
    test_parse_meta(i);
    test_parse_paylen_7(i);
    test_parse_paylen_16(i);
    test_parse_paylen_64(i);
    test_parse_unmask(i);
  }

  test_mask();
  test_unmask_max();
  test_enc_frame_meta();
  test_enc_frame_paylen_7();
  test_enc_frame_paylen_16();
  test_enc_frame_paylen_64();
  test_enc_frame_paylen_max();
  test_enc_frame_mask_key();
  test_enc_ctrl();
  test_enc_ctrl_masked();
  test_enc_ctrl_len();
  test_enc_ctrl_len_max();
  test_enc_ping();
  test_enc_pong();
  test_enc_close();
  test_enc_close_status();
  test_enc_close_status_mask();
  test_print_meta();
  test_print_meta_empty();
  test_print_meta_paylen();
  test_print_meta_mask_key();

  mu_assert(sp_alloc_summary());
}
