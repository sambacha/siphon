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

#define SP_WS_LEN_7    125
#define SP_WS_LEN_16   126
#define SP_WS_LEN_64   127

typedef union {
	// frame metadata
	struct {
		bool fin;
		bool rsv1;
		bool rsv2;
		bool rsv3;
		uint8_t opcode;
		bool mask;
		uint8_t lencode;
	};

	// 7-bit payload length
	struct {
		uint8_t len_7;
	};

	// 16-bit payload length
	struct {
		uint16_t len_16;
	};

	// 64-bit payload length
	struct {
		uint64_t len_64;
	};

	// masking key
	struct {
		uint32_t masking_key;
	};

	// beginning of payload
	struct {
		size_t length;
	} payload;
} SpWsFrame;

typedef enum {
	SP_WS_NONE = -1,
	SP_WS_META,          // FIN flag, 3 RSV flags, opcode, MASK flag, lencode
	SP_WS_PAYLOAD_LEN,   // length of the payload
	SP_WS_MASKING_KEY,   // masking key for clients
	SP_WS_PAYLOAD_START, // start of the payload data
	SP_WS_PAYLOAD_END,   // end of the payload data
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
