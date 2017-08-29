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

// length codes

#define SP_WS_EMPTY    0
#define SP_WS_LEN_8    125
#define SP_WS_LEN_16   126
#define SP_WS_LEN_64   127

typedef struct {
	// frame metadata
	bool fin;
	bool rsv1;
	bool rsv2;
	bool rsv3;
	uint8_t opcode;
	bool mask;
	uint8_t lencode;

	// 8-bit, 16-bit or 64-bit payload length
	union {
		uint8_t u8;
		uint16_t u16;
		uint64_t u64;
	} len;

	// masking key
	uint8_t masking_key[4];

	// beginning of payload
	uint8_t *payload;
} SpWsFrame;

typedef enum {
	SP_WS_NONE = -1,
	SP_WS_META,          // FIN flag, 3 RSV flags, opcode, MASK flag, lencode
	SP_WS_PAYLOAD_LEN,   // length of the payload
	SP_WS_MASKING_KEY,   // masking key for clients
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
	size_t payload_len;  // payload length
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

SP_EXPORT void
sp_ws_print (const SpWs *p, const void *restrict buf, FILE *out);

#endif
