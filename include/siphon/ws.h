#ifndef SIPHON_WS_H
#define SIPHON_WS_H

#include "common.h"
#include "range.h"

// opcodes

#define SP_WS_PONG     0xa
#define SP_WS_PING     0x9
#define SP_WS_CLOSE    0x8
#define SP_WS_BIN      0x2
#define SP_WS_TEXT     0x1
#define SP_WS_CONT     0x0

typedef enum {
	SP_WS_LEN_NONE = -1,
	SP_WS_LEN_7,
	SP_WS_LEN_16,
	SP_WS_LEN_64,
} SpWsLenType;

typedef struct {
	// frame metadata
	bool fin;
	bool rsv1;
	bool rsv2;
	bool rsv3;
	uint8_t opcode;
	bool masked;

	// 7-bit payload length or extended 16-bit/64-bit payload length
	struct {
		SpWsLenType type;  // the type of the payload length
		union {
			uint8_t u7;      // 0 <= encoded paylen <= 125
			uint16_t u16;    // encoded paylen == 126
			uint64_t u64;    // encoded paylen == 127
		} len;
	} paylen;

	// masking key
	uint8_t mask_key[4];

	// beginning of payload
	uint8_t *payload;
} SpWsFrame;

typedef enum {
	SP_WS_NONE = -1,
	SP_WS_META,          // FIN flag, 3 RSV flags, opcode, MASK flag, lencode
	SP_WS_PAYLEN,        // length of the payload
	SP_WS_MASK_KEY,      // masking key, for servers only
} SpWsType;

typedef struct {
	// readonly
	uint16_t scans;      // number of passes through the scanner
	uint8_t cscans;      // number of scans in the current rule
	bool client;         // true if client, false if server
	SpWsFrame as;        // captured value
	SpWsType type;       // type of the captured value
	unsigned cs;         // current scanner state
	size_t off;          // internal offset mark
} SpWs;


SP_EXPORT int
sp_ws_init_client (SpWs *p);

SP_EXPORT int
sp_ws_init_server (SpWs *p);

SP_EXPORT void
sp_ws_reset (SpWs *p);

SP_EXPORT ssize_t
sp_ws_next (SpWs *p, const void *restrict buf, size_t len);

SP_EXPORT bool
sp_ws_is_done (const SpWs *p);

SP_EXPORT size_t
sp_ws_mask (void *dst, const void *restrict buf, size_t len, uint8_t *key);

#endif
