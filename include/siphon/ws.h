#ifndef SIPHON_WS_H
#define SIPHON_WS_H

#include "common.h"
#include "range.h"

typedef enum {
	SpWsNonCtrlType = 0x0,
	SpWsCtrlType = 0x8
} SpWsOpcode;

typedef enum {
	SP_WS_CONT = SpWsNonCtrlType,
	SP_WS_TEXT,
	SP_WS_BIN ,
} SpWsNonCtrlOpcode;

typedef enum {
	SP_WS_CLOSE = SpWsCtrlType,
	SP_WS_PING,
	SP_WS_PONG,
} SpWsCtrlOpcode;

typedef enum {
	SP_WS_LEN_NONE = 0,
	SP_WS_LEN_7,
	SP_WS_LEN_16,
	SP_WS_LEN_64,
} SpWsLenType;

typedef enum {
	SP_WS_STATUS_NONE   = 0,
	SP_WS_STATUS_NORMAL = 1000,
	SP_WS_STATUS_AWAY   = 1001,
	SP_WS_STATUS_PROTO  = 1002,
	SP_WS_STATUS_TYPE   = 1004,
	SP_WS_STATUS_DATA   = 1007,
	SP_WS_STATUS_POLICY = 1008,
	SP_WS_STATUS_BIG    = 1009,
	SP_WS_STATUS_EXT    = 1010,
	SP_WS_STATUS_FAIL   = 1011,
} SpWsStatus;

typedef struct {
	// frame metadata
	bool fin;
	bool rsv1;
	bool rsv2;
	bool rsv3;
	SpWsOpcode opcode;
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
} SpWsFrame;

// parser states
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

SP_EXPORT ssize_t
sp_ws_enc_frame (void *buf, const SpWsFrame *restrict f);

SP_EXPORT ssize_t
sp_ws_enc_ctrl (void *m, const SpWsCtrlOpcode code, const size_t len, const uint8_t *key);

SP_EXPORT ssize_t
sp_ws_enc_ping (void *m, const size_t len, const uint8_t *key);

SP_EXPORT ssize_t
sp_ws_enc_pong (void *m, const size_t len, const uint8_t *key);

SP_EXPORT ssize_t
sp_ws_enc_close (void *m, SpWsStatus stat, const size_t len, const uint8_t *key);

SP_EXPORT const char *
sp_ws_status_string (SpWsStatus stat);

#endif
