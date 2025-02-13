#include "../include/siphon/utf8.h"
#include "../include/siphon/alloc.h"
#include "../include/siphon/error.h"
#include "parser.h"

#include "pcmp/range.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define MAX_POWER_OF_2 16384

/*
 * Code point      Size  1st     2nd     3rd     4th
 * --------------  ----  ------  ------  ------  ------
 * 000000..00007F  1     00..7F
 * 000080..0007FF  2     C0..DF  80..BF
 * 000800..000FFF  3     E0      A0..BF  80..BF
 * 001000..00FFFF  3     E1..EF  80..BF  80..BF
 * 010000..03FFFF  4     F0      90..BF  80..BF  80..BF
 * 040000..0FFFFF  4     F1..F3  80..BF  80..BF  80..BF
 * 100000..10FFFF  4     F4      80..8F  80..BF  80..BF
 */

static const uint8_t byte_counts[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static bool is_cont(uint8_t b) { return 0x80 <= b && b <= 0xBF; }

static inline bool is_surrogate(int cp) { return 0xD800 <= cp && cp <= 0xDFFF; }

static inline int combine_surrogate(int hi, int lo) {
  return (hi - 0xD800) * 0x400 + (lo - 0xDC00) + 0x10000;
}

static inline bool is_valid_json_byte(const uint8_t *src) {
  return *src >= 0x1F && *src != 0x7F;
}

static inline uint8_t hex1(const uint8_t *p) {
  static const uint8_t map[128] = {
      ['0'] = 0, 1,  2,  3,  4,  5,          6,  7,  8,  9,  ['A'] = 10,
      11,        12, 13, 14, 15, ['a'] = 10, 11, 12, 13, 14, 15};
  return map[*p];
}

static inline uint8_t hex2(const uint8_t *p) {
  return (hex1(p) << 4) | hex1(p + 1);
}

static inline uint16_t hex4(const uint8_t *p) {
  return (hex1(p) << 12) | (hex1(p + 1) << 8) | (hex1(p + 2) << 4) |
         hex1(p + 3);
}

static inline bool is_hex2(const uint8_t *p) {
  return isxdigit(p[0]) && isxdigit(p[1]);
}

static inline bool is_hex4(const uint8_t *p) {
  return is_hex2(p) && is_hex2(p + 2);
}

static inline void to_hex(uint8_t ch, char out[static 2]) {
  static const char enc[16] = "0123456789ABCDEF";
  out[0] = enc[ch >> 4];
  out[1] = enc[ch & 0xf];
}

static ssize_t unescape(SpUtf8 *u, const uint8_t *src, ssize_t rem) {
  if (rem < 2) {
    return SP_UTF8_ETOOSHORT;
  }

  int cp;
  size_t scan = 0;

  switch (src[1]) {
  case 'b':
    scan = 2;
    cp = '\b';
    break;
  case 'f':
    scan = 2;
    cp = '\f';
    break;
  case 'n':
    scan = 2;
    cp = '\n';
    break;
  case 'r':
    scan = 2;
    cp = '\r';
    break;
  case 't':
    scan = 2;
    cp = '\t';
    break;
  case '"':
    scan = 2;
    cp = '"';
    break;
  case '/':
    scan = 2;
    cp = '/';
    break;
  case '\\':
    scan = 2;
    cp = '\\';
    break;
  case 'u':
    if (rem < 6)
      return SP_UTF8_ETOOSHORT;
    if (!is_hex4(src + 2))
      return SP_UTF8_EESCAPE;

    cp = hex4(src + 2);
    if (is_surrogate(cp)) {
      if ((rem > 6 && src[6] != '\\') || (rem > 7 && src[7] != 'u')) {
        return SP_UTF8_ESURROGATE;
      }
      if (rem < 12)
        return SP_UTF8_ETOOSHORT;
      if (!is_hex4(src + 8))
        return SP_UTF8_EESCAPE;
      cp = combine_surrogate(cp, hex4(src + 8));
      scan = 12;
    } else {
      scan = 6;
    }

    break;
  default:
    return SP_UTF8_EESCAPE;
  }

  ssize_t rc = sp_utf8_add_codepoint(u, cp);
  return rc < 0 ? rc : (ssize_t)scan;
}

static inline ssize_t add_escape(SpUtf8 *u, const void *esc) {
  ssize_t rc = sp_utf8_add_raw(u, esc, 2);
  return rc < 0 ? rc : 1;
}

static ssize_t pct_decode(SpUtf8 *u, const uint8_t *src, ssize_t rem) {
  assert(*src == '%');

  uint8_t in[4];
  in[0] = hex2(src + 1);

  uint8_t inlen = byte_counts[in[0]];
  if (rem < 3 * inlen) {
    return SP_UTF8_ETOOSHORT;
  }

  switch (inlen) {
  case 0:
    return SP_UTF8_EENCODING;
  case 4:
    in[3] = hex2(src + 10);
  case 3:
    in[2] = hex2(src + 7);
  case 2:
    in[1] = hex2(src + 4);
  }

  ssize_t rc = sp_utf8_add_char(u, in, inlen);
  if (rc < 0) {
    return rc;
  }

  return 3 * inlen;
}

static inline ssize_t
codec(SpUtf8 *u, const uint8_t *p, const uint8_t *pe, const uint8_t *rng,
      size_t rnglen, ssize_t (*next)(SpUtf8 *u, const void *src, size_t len)) {
  ssize_t start = u->len;

  while (p < pe) {
    const uint8_t *m = pcmp_range(p, pe - p, rng, rnglen);
    if (m == NULL) {
      break;
    }

    sp_utf8_add_raw(u, p, m - p);
    p = m;

    ssize_t n = next(u, p, pe - p);
    if (n < 0) {
      return n;
    }
    p += n;
  }

  sp_utf8_add_raw(u, p, pe - p);
  return u->len - start;
}

void sp_utf8_init(SpUtf8 *u) {
  assert(u != NULL);

  *u = SP_UTF8_MAKE();
}

void sp_utf8_init_fixed(SpUtf8 *u, void *buf, size_t len) {
  assert(u != NULL);

  *u = SP_UTF8_MAKE_FIXED(buf, len);
}

void sp_utf8_reset(SpUtf8 *u) {
  assert(u != NULL);

  if (u->buf != NULL) {
    u->buf[0] = '\0';
  }
  u->len = 0;
}

void sp_utf8_final(SpUtf8 *u) {
  assert(u != NULL);

  if (!u->fixed) {
    sp_free(u->buf, u->cap);
  }
  *u = SP_UTF8_MAKE();
}

uint8_t *sp_utf8_steal(SpUtf8 *u, size_t *len, size_t *cap) {
  assert(u != NULL);

  uint8_t *buf = u->buf;
  if (len)
    *len = u->len;
  if (cap)
    *cap = u->cap;
  *u = SP_UTF8_MAKE();
  return buf;
}

size_t sp_utf8_copy(const SpUtf8 *u, void *buf, size_t len) {
  assert(u != NULL);

  size_t out = u->len;
  if (out >= len) {
    out = len - 1;
  }
  memcpy(buf, u->buf, out);
  ((char *)buf)[out] = '\0';
  return out;
}

int sp_utf8_ensure(SpUtf8 *u, size_t len) {
  assert(u != NULL);

  if (len > (ssize_t)((size_t)SIZE_MAX / 2)) {
    return SP_UTF8_ESIZE;
  }

  // add 1 to ensure space for a NUL byte
  size_t cap = u->len + len + 1;

  // check if we already have enough space
  if (cap <= u->cap) {
    return 0;
  }

  // check if we have a fixed buffer
  if (u->fixed) {
    return SP_UTF8_EBUFS;
  }

  // round up required capacity
  if (cap < 64) {
    cap = 64;
  } else if (cap < MAX_POWER_OF_2) {
    // calculate the next power of 2
    cap = sp_power_of_2(cap);
  } else {
    // calculate the nearest multiple of MAX_POWER_OF_2
    cap = sp_next_quantum(cap, MAX_POWER_OF_2);
  }

  uint8_t *buf = sp_realloc(u->buf, u->cap, cap);
  if (buf == NULL) {
    return SP_ESYSTEM(errno);
  }
  u->buf = buf;
  u->cap = cap;
  return 0;
}

ssize_t sp_utf8_add_raw(SpUtf8 *u, const void *src, size_t len) {
  assert(u != NULL);

  if (len == 0) {
    return 0;
  }

  int rc = sp_utf8_ensure(u, len);
  if (rc < 0) {
    return rc;
  }

  memcpy(u->buf + u->len, src, len);
  u->len += len;
  u->buf[u->len] = '\0';
  return (ssize_t)len;
}

ssize_t sp_utf8_add_codepoint(SpUtf8 *u, int cp) {
  assert(u != NULL);

  uint8_t buf[4], len = 0;

  if (cp < 0x80) {
    if (cp < 0) {
      return SP_UTF8_ECODEPOINT;
    }
    buf[0] = cp;
    len = 1;
  } else if (cp < 0x800) {
    buf[0] = (cp >> 6) | 0xC0;
    buf[1] = (cp & 0x3F) | 0x80;
    len = 2;
  } else if (cp < 0x10000) {
    buf[0] = (cp >> 12) | 0xE0;
    buf[1] = ((cp >> 6) & 0x3F) | 0x80;
    buf[2] = (cp & 0x3F) | 0x80;
    len = 3;
  } else if (cp < 0x110000) {
    buf[0] = (cp >> 18) | 0xF0;
    buf[1] = ((cp >> 12) & 0x3F) | 0x80;
    buf[2] = ((cp >> 6) & 0x3F) | 0x80;
    buf[3] = (cp & 0x3F) | 0x80;
    len = 4;
  } else {
    return SP_UTF8_ECODEPOINT;
  }

  return sp_utf8_add_raw(u, buf, len);
}

ssize_t sp_utf8_add_char(SpUtf8 *u, const void *src, size_t len) {
  assert(u != NULL);

  ssize_t charlen = sp_utf8_charlen(src, len);
  if (charlen <= 0) {
    return charlen;
  }

  return sp_utf8_add_raw(u, src, charlen);
}

static const uint8_t rng_json[] = "\0\x1f\"\"\\\\\x7f\xff";

// generated from test-utf8-encode tool
static const uint8_t rng_enc_uri[] = "\0 \"\"%%<<>>[^``{}\x7f\xff";
static const uint8_t rng_enc_uri_comp[] = "\0 \"&+,//:@[^``{}\x7f\xff";

static const uint8_t rng_dec_uri[] = "%%\x80\xff";
static const uint8_t rng_dec_uri_space[] = "%%++\x80\xff";

static inline ssize_t json_encode(SpUtf8 *u, const void *src, size_t len) {
  switch (*(const uint8_t *)src) {
  case '"':
    return add_escape(u, "\\\"");
  case '\\':
    return add_escape(u, "\\\\");
  case '\b':
    return add_escape(u, "\\b");
  case '\f':
    return add_escape(u, "\\f");
  case '\n':
    return add_escape(u, "\\n");
  case '\r':
    return add_escape(u, "\\r");
  case '\t':
    return add_escape(u, "\\t");
  }

  if (!is_valid_json_byte(src)) {
    return SP_UTF8_EENCODING;
  }

  return sp_utf8_add_char(u, src, len);
}

static inline ssize_t json_decode(SpUtf8 *u, const void *src, size_t len) {
  // check for control characters
  if (!is_valid_json_byte(src)) {
    return SP_JSON_EBYTE;
  }

  return *(const uint8_t *)src == '\\' ? unescape(u, src, len)
                                       : sp_utf8_add_char(u, src, len);
}

static inline ssize_t uri_encode(SpUtf8 *u, const void *src, size_t len) {
  ssize_t charlen = sp_utf8_charlen(src, len);
  if (charlen <= 0) {
    return charlen;
  }

  char buf[12];
  for (ssize_t i = 0; i < charlen; i++) {
    buf[i * 3] = '%';
    to_hex(((const uint8_t *)src)[i], &buf[i * 3 + 1]);
  }

  ssize_t rc = sp_utf8_add_raw(u, buf, charlen * 3);
  if (rc < 0) {
    return rc;
  }

  return charlen;
}

static inline ssize_t uri_encode_space(SpUtf8 *u, const void *src, size_t len) {
  if (*(const uint8_t *)src == ' ') {
    return sp_utf8_add_raw(u, "+", 1);
  }
  return uri_encode(u, src, len);
}

static inline ssize_t uri_decode(SpUtf8 *u, const void *src, size_t len) {
  if (*(const uint8_t *)src == '%') {
    return pct_decode(u, src, len);
  }
  return sp_utf8_add_char(u, src, len);
}

static inline ssize_t uri_decode_space(SpUtf8 *u, const void *src, size_t len) {
  switch (*(const uint8_t *)src) {
  case '%':
    return pct_decode(u, src, len);
  case '+':
    return sp_utf8_add_char(u, " ", 1);
  default:
    return sp_utf8_add_char(u, src, len);
  }
}

ssize_t sp_utf8_encode(SpUtf8 *u, const void *src, size_t len, SpUtf8Flags f) {
  assert(u != NULL);

  const uint8_t *rng;
  size_t rnglen;
  ssize_t (*next)(SpUtf8 * u, const void *src, size_t len);

  if (f & SP_UTF8_JSON) {
    rng = rng_json;
    rnglen = sizeof rng_json - 1;
    next = json_encode;
  } else {
    if (f & SP_UTF8_URI_COMPONENT) {
      rng = rng_enc_uri_comp;
      rnglen = sizeof rng_enc_uri_comp - 1;
    } else {
      rng = rng_enc_uri;
      rnglen = sizeof rng_enc_uri - 1;
    }
    if (f & SP_UTF8_SPACE_PLUS) {
      next = uri_encode_space;
    } else {
      next = uri_encode;
    }
  }

  return codec(u, src, (const uint8_t *)src + len, rng, rnglen, next);
}

ssize_t sp_utf8_decode(SpUtf8 *u, const void *src, size_t len, SpUtf8Flags f) {
  assert(u != NULL);

  const uint8_t *rng;
  size_t rnglen;
  ssize_t (*next)(SpUtf8 * u, const void *src, size_t len);

  if (f & SP_UTF8_JSON) {
    rng = rng_json;
    rnglen = sizeof rng_json - 1;
    next = json_decode;
  } else if (f & SP_UTF8_SPACE_PLUS) {
    rng = rng_dec_uri_space;
    rnglen = sizeof rng_dec_uri_space - 1;
    next = uri_decode_space;
  } else {
    rng = rng_dec_uri;
    rnglen = sizeof rng_dec_uri - 1;
    next = uri_decode;
  }

  return codec(u, src, (const uint8_t *)src + len, rng, rnglen, next);
}

ssize_t sp_utf8_json_encode(SpUtf8 *u, const void *src, size_t len,
                            SpUtf8Flags f) {
  (void)f;

  assert(u != NULL);
  assert(src != NULL);

  if (len == 0) {
    return SP_UTF8_ETOOSHORT;
  }

  return json_encode(u, src, len);
}

ssize_t sp_utf8_json_decode(SpUtf8 *u, const void *src, size_t len,
                            SpUtf8Flags f) {
  (void)f;

  assert(u != NULL);
  assert(src != NULL);

  if (len == 0) {
    return SP_UTF8_ETOOSHORT;
  }

  return json_decode(u, src, len);
}

ssize_t sp_utf8_uri_decode(SpUtf8 *u, const void *src, size_t len,
                           SpUtf8Flags f) {
  assert(u != NULL);
  assert(src != NULL);

  if (len == 0) {
    return SP_UTF8_ETOOSHORT;
  }

  if (f & SP_UTF8_SPACE_PLUS) {
    return uri_decode_space(u, src, len);
  }
  return uri_decode(u, src, len);
}

ssize_t sp_utf8_uri_encode(SpUtf8 *u, const void *src, size_t len,
                           SpUtf8Flags f) {
  assert(u != NULL);
  assert(src != NULL);

  if (len == 0) {
    return SP_UTF8_ETOOSHORT;
  }

  uint8_t ch = *(const uint8_t *)src;

  if ((f & SP_UTF8_URI_COMPONENT)
          ? memchr(rng_enc_uri_comp, ch, sizeof rng_enc_uri_comp - 1)
          : memchr(rng_enc_uri, ch, sizeof rng_enc_uri - 1)) {
    if (f & SP_UTF8_SPACE_PLUS) {
      return uri_encode_space(u, src, len);
    }
    return uri_encode(u, src, len);
  }

  return sp_utf8_add_raw(u, src, 1);
}

int sp_utf8_codepoint(const void *src, size_t len) {
  assert(src != NULL);

  if (len == 0) {
    return SP_UTF8_ETOOSHORT;
  }

  const uint8_t *m = src;
  int cp1, cp2, cp3, cp4;

  cp1 = m[0];
  if (cp1 < 0x80) {
    return cp1;
  } else if (cp1 < 0xC2) {
    return SP_UTF8_EENCODING;
  } else if (cp1 < 0xE0) {
    if (len < 2) {
      return SP_UTF8_ETOOSHORT;
    }
    cp2 = m[1];
    if ((cp2 & 0xC0) != 0x80) {
      return SP_UTF8_EENCODING;
    }
    return (cp1 << 6) + cp2 - 0x3080;
  } else if (cp1 < 0xF0) {
    if (len < 3) {
      return SP_UTF8_ETOOSHORT;
    }
    cp2 = m[1];
    if ((cp2 & 0xC0) != 0x80 || (cp1 == 0xE0 && cp2 < 0xA0)) {
      return SP_UTF8_EENCODING;
    }
    cp3 = m[2];
    if ((cp3 & 0xC0) != 0x80) {
      return SP_UTF8_EENCODING;
    }
    return (cp1 << 12) + (cp2 << 6) + cp3 - 0xE2080;
  } else if (cp1 < 0xF5) {
    if (len < 4) {
      return SP_UTF8_ETOOSHORT;
    }
    cp2 = m[1];
    if ((cp2 & 0xC0) != 0x80 || (cp1 == 0xF0 && cp2 < 0x90) ||
        (cp1 == 0xF4 && cp2 >= 0x90)) {
      return SP_UTF8_EENCODING;
    }
    cp3 = m[2];
    if ((cp3 & 0xC0) != 0x80) {
      return SP_UTF8_EENCODING;
    }
    cp4 = m[3];
    if ((cp4 & 0xC0) != 0x80) {
      return SP_UTF8_EENCODING;
    }
    return (cp1 << 18) + (cp2 << 12) + (cp3 << 6) + cp4 - 0x3C82080;
  } else {
    return SP_UTF8_EENCODING;
  }
}

ssize_t sp_utf8_charlen(const void *src, size_t len) {
  if (len == 0) {
    return 0;
  }

  const uint8_t *in = src;

  if (!(*in & 0x80)) {
    return 1;
  }

  switch (in[0]) {

  case 0xE0:
    if (len < 3)
      return SP_UTF8_ETOOSHORT;
    if (in[1] < 0xA0 || 0xBF < in[1]) {
      return SP_UTF8_EENCODING;
    }
    if (!is_cont(in[2])) {
      return SP_UTF8_EENCODING;
    }
    return 3;

  case 0xF0:
    if (len < 4)
      return SP_UTF8_ETOOSHORT;
    if (in[1] < 0x90 || 0xBF < in[1]) {
      return SP_UTF8_EENCODING;
    }
    if (!is_cont(in[2]) || !is_cont(in[3])) {
      return SP_UTF8_EENCODING;
    }
    return 4;
  }

  size_t charlen = byte_counts[in[0]];
  if (len < charlen)
    return SP_UTF8_ETOOSHORT;

  switch (charlen) {
  case 0:
    return SP_UTF8_EENCODING;
  case 4:
    if (!is_cont(in[3]))
      return SP_UTF8_EENCODING;
  case 3:
    if (!is_cont(in[2]))
      return SP_UTF8_EENCODING;
  case 2:
    if (!is_cont(in[1]))
      return SP_UTF8_EENCODING;
  }

  return charlen;
}
