
#line 1 "/Users/sbacha/siphon/lib/uri_parser.rl"
#include "siphon/uri.h"

#include <assert.h>


#line 151 "/Users/sbacha/siphon/lib/uri_parser.rl"



ssize_t
sp_uri_parse (SpUri *u, const char *restrict buf, size_t len)
{
	assert (u != NULL);
	assert (buf != NULL);

	const char *restrict p = buf;
	const char *restrict pe = p + len;
	const char *restrict eof = pe;
	const char *restrict mark = p;
	const char *restrict user = NULL;
	const char *restrict pass = NULL;
	int cs = 204;
	bool mapped = false;

	memset (u->seg, 0, sizeof u->seg);
	u->port = 0;
	u->first = SP_URI_NONE;
	u->last = SP_URI_NONE;
	u->host = SP_HOST_NONE;

#define SET(name, back) do {              \
	if (u->first == SP_URI_NONE) {        \
		u->first = SP_URI_##name;         \
	}                                     \
	u->last = SP_URI_##name;              \
	u->seg[SP_URI_##name] = (SpRange16) { \
		mark-buf,                         \
		p-mark-back                       \
	};                                    \
} while (0)
	
#line 45 "/Users/sbacha/siphon/build/uri_parser.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 204:
	switch( (*p) ) {
		case -32: goto tr188;
		case -16: goto tr190;
		case -12: goto tr192;
		case 35: goto tr194;
		case 37: goto tr195;
		case 47: goto tr196;
		case 63: goto tr197;
		case 92: goto tr193;
	}
	if ( (*p) < 59 ) {
		if ( (*p) < -31 ) {
			if ( -64 <= (*p) && (*p) <= -33 )
				goto tr187;
		} else if ( (*p) > -17 ) {
			if ( (*p) > -13 ) {
				if ( 33 <= (*p) && (*p) <= 57 )
					goto tr193;
			} else if ( (*p) >= -15 )
				goto tr191;
		} else
			goto tr189;
	} else if ( (*p) > 64 ) {
		if ( (*p) < 94 ) {
			if ( 65 <= (*p) && (*p) <= 90 )
				goto tr198;
		} else if ( (*p) > 96 ) {
			if ( (*p) > 122 ) {
				if ( 123 <= (*p) && (*p) <= 126 )
					goto tr193;
			} else if ( (*p) >= 97 )
				goto tr198;
		} else
			goto tr193;
	} else
		goto tr193;
	goto st0;
st0:
cs = 0;
	goto _out;
tr187:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 100 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st205;
	goto st0;
tr193:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st205;
st205:
	if ( ++p == pe )
		goto _test_eof205;
case 205:
#line 112 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto st2;
		case -16: goto st4;
		case -12: goto st6;
		case 35: goto tr203;
		case 37: goto st15;
		case 47: goto st208;
		case 63: goto tr205;
		case 92: goto st205;
	}
	if ( (*p) < -15 ) {
		if ( (*p) > -33 ) {
			if ( -31 <= (*p) && (*p) <= -17 )
				goto st3;
		} else if ( (*p) >= -64 )
			goto st1;
	} else if ( (*p) > -13 ) {
		if ( (*p) < 59 ) {
			if ( 33 <= (*p) && (*p) <= 57 )
				goto st205;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 126 )
				goto st205;
		} else
			goto st205;
	} else
		goto st5;
	goto st0;
tr188:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 149 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( -96 <= (*p) && (*p) <= -65 )
		goto st1;
	goto st0;
tr189:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 161 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st1;
	goto st0;
tr190:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 173 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( -112 <= (*p) && (*p) <= -65 )
		goto st3;
	goto st0;
tr191:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 185 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st3;
	goto st0;
tr192:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 197 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -113 )
		goto st3;
	goto st0;
tr194:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st206;
tr203:
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st206;
tr231:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 18 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(QUERY, 0); }
	goto st206;
tr237:
#line 18 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(QUERY, 0); }
	goto st206;
tr249:
#line 14 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_NAME; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st206;
tr255:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 15 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PORT, 0); }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st206;
tr270:
#line 15 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PORT, 0); }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st206;
tr289:
#line 10 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_IPV4; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st206;
st206:
	if ( ++p == pe )
		goto _test_eof206;
case 206:
#line 257 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto tr207;
		case -16: goto tr209;
		case -12: goto tr211;
		case 37: goto tr213;
	}
	if ( (*p) < -31 ) {
		if ( -64 <= (*p) && (*p) <= -33 )
			goto tr206;
	} else if ( (*p) > -17 ) {
		if ( (*p) > -13 ) {
			if ( 33 <= (*p) && (*p) <= 126 )
				goto tr212;
		} else if ( (*p) >= -15 )
			goto tr210;
	} else
		goto tr208;
	goto st0;
tr206:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 284 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st207;
	goto st0;
tr212:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st207;
st207:
	if ( ++p == pe )
		goto _test_eof207;
case 207:
#line 296 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto st8;
		case -16: goto st10;
		case -12: goto st12;
		case 37: goto st13;
	}
	if ( (*p) < -31 ) {
		if ( -64 <= (*p) && (*p) <= -33 )
			goto st7;
	} else if ( (*p) > -17 ) {
		if ( (*p) > -13 ) {
			if ( 33 <= (*p) && (*p) <= 126 )
				goto st207;
		} else if ( (*p) >= -15 )
			goto st11;
	} else
		goto st9;
	goto st0;
tr207:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 323 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( -96 <= (*p) && (*p) <= -65 )
		goto st7;
	goto st0;
tr208:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 335 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st7;
	goto st0;
tr209:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 347 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( -112 <= (*p) && (*p) <= -65 )
		goto st9;
	goto st0;
tr210:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 359 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st9;
	goto st0;
tr211:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 371 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -113 )
		goto st9;
	goto st0;
tr213:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 383 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st14;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st14;
	} else
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st207;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st207;
	} else
		goto st207;
	goto st0;
tr195:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 414 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st16;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st16;
	} else
		goto st16;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st205;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st205;
	} else
		goto st205;
	goto st0;
tr242:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st208;
tr251:
#line 14 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_NAME; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st208;
tr257:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 15 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PORT, 0); }
	goto st208;
tr271:
#line 15 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PORT, 0); }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st208;
tr290:
#line 10 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_IPV4; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st208;
st208:
	if ( ++p == pe )
		goto _test_eof208;
case 208:
#line 469 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto st18;
		case -16: goto st20;
		case -12: goto st22;
		case 35: goto tr203;
		case 37: goto st23;
		case 63: goto tr205;
	}
	if ( (*p) < -31 ) {
		if ( -64 <= (*p) && (*p) <= -33 )
			goto st17;
	} else if ( (*p) > -17 ) {
		if ( (*p) > -13 ) {
			if ( 33 <= (*p) && (*p) <= 126 )
				goto st208;
		} else if ( (*p) >= -15 )
			goto st21;
	} else
		goto st19;
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) <= -65 )
		goto st208;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( -96 <= (*p) && (*p) <= -65 )
		goto st17;
	goto st0;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) <= -65 )
		goto st17;
	goto st0;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( -112 <= (*p) && (*p) <= -65 )
		goto st19;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) <= -65 )
		goto st19;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) <= -113 )
		goto st19;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st24;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st24;
	} else
		goto st24;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st208;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st208;
	} else
		goto st208;
	goto st0;
tr197:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st209;
tr205:
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st209;
tr253:
#line 14 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_NAME; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st209;
tr259:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 15 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PORT, 0); }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st209;
tr273:
#line 15 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PORT, 0); }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st209;
tr292:
#line 10 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_IPV4; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	goto st209;
st209:
	if ( ++p == pe )
		goto _test_eof209;
case 209:
#line 604 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto tr225;
		case -16: goto tr227;
		case -12: goto tr229;
		case 35: goto tr231;
		case 37: goto tr232;
	}
	if ( (*p) < -31 ) {
		if ( -64 <= (*p) && (*p) <= -33 )
			goto tr224;
	} else if ( (*p) > -17 ) {
		if ( (*p) > -13 ) {
			if ( 33 <= (*p) && (*p) <= 126 )
				goto tr230;
		} else if ( (*p) >= -15 )
			goto tr228;
	} else
		goto tr226;
	goto st0;
tr224:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 632 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st210;
	goto st0;
tr230:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st210;
st210:
	if ( ++p == pe )
		goto _test_eof210;
case 210:
#line 644 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto st26;
		case -16: goto st28;
		case -12: goto st30;
		case 35: goto tr237;
		case 37: goto st31;
	}
	if ( (*p) < -31 ) {
		if ( -64 <= (*p) && (*p) <= -33 )
			goto st25;
	} else if ( (*p) > -17 ) {
		if ( (*p) > -13 ) {
			if ( 33 <= (*p) && (*p) <= 126 )
				goto st210;
		} else if ( (*p) >= -15 )
			goto st29;
	} else
		goto st27;
	goto st0;
tr225:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 672 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( -96 <= (*p) && (*p) <= -65 )
		goto st25;
	goto st0;
tr226:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st27;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
#line 684 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st25;
	goto st0;
tr227:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 696 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( -112 <= (*p) && (*p) <= -65 )
		goto st27;
	goto st0;
tr228:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 708 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st27;
	goto st0;
tr229:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 720 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -113 )
		goto st27;
	goto st0;
tr232:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 732 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st32;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st32;
	} else
		goto st32;
	goto st0;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st210;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st210;
	} else
		goto st210;
	goto st0;
tr196:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st211;
st211:
	if ( ++p == pe )
		goto _test_eof211;
case 211:
#line 763 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto st18;
		case -16: goto st20;
		case -12: goto st22;
		case 35: goto tr203;
		case 37: goto st23;
		case 47: goto st212;
		case 63: goto tr205;
	}
	if ( (*p) < -31 ) {
		if ( -64 <= (*p) && (*p) <= -33 )
			goto st17;
	} else if ( (*p) > -17 ) {
		if ( (*p) > -13 ) {
			if ( 33 <= (*p) && (*p) <= 126 )
				goto st208;
		} else if ( (*p) >= -15 )
			goto st21;
	} else
		goto st19;
	goto st0;
st212:
	if ( ++p == pe )
		goto _test_eof212;
case 212:
	switch( (*p) ) {
		case 33: goto tr240;
		case 35: goto tr194;
		case 37: goto tr241;
		case 47: goto tr242;
		case 48: goto tr243;
		case 49: goto tr244;
		case 50: goto tr245;
		case 58: goto st214;
		case 59: goto tr240;
		case 61: goto tr240;
		case 63: goto tr197;
		case 64: goto tr21;
		case 91: goto st40;
		case 95: goto tr240;
		case 126: goto tr240;
	}
	if ( (*p) < 51 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto tr240;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr240;
		} else if ( (*p) >= 65 )
			goto tr240;
	} else
		goto tr246;
	goto st0;
tr240:
#line 20 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ user = p; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st213;
st213:
	if ( ++p == pe )
		goto _test_eof213;
case 213:
#line 828 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 47: goto tr251;
		case 58: goto tr252;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st213;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st213;
	} else
		goto st213;
	goto st0;
tr241:
#line 20 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ user = p; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st33;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
#line 860 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st34;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st34;
	} else
		goto st34;
	goto st0;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st213;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st213;
	} else
		goto st213;
	goto st0;
tr252:
#line 14 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_NAME; }
	goto st214;
tr315:
#line 10 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_IPV4; }
	goto st214;
st214:
	if ( ++p == pe )
		goto _test_eof214;
case 214:
#line 895 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto tr254;
		case 35: goto tr255;
		case 37: goto tr256;
		case 47: goto tr257;
		case 59: goto tr254;
		case 61: goto tr254;
		case 63: goto tr259;
		case 95: goto tr254;
		case 126: goto tr254;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto tr254;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr254;
		} else if ( (*p) >= 65 )
			goto tr254;
	} else
		goto tr258;
	goto st0;
tr254:
#line 21 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ pass = p; }
	goto st35;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
#line 927 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st35;
		case 37: goto st36;
		case 59: goto st35;
		case 61: goto st35;
		case 64: goto tr21;
		case 95: goto st35;
		case 126: goto st35;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st35;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st35;
		} else if ( (*p) >= 65 )
			goto st35;
	} else
		goto st35;
	goto st0;
tr256:
#line 21 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ pass = p; }
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 957 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st37;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st37;
	} else
		goto st37;
	goto st0;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st35;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st35;
	} else
		goto st35;
	goto st0;
tr21:
#line 22 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{
		size_t back;
		if (pass == NULL) {
			back = 0;
		}
		else {
			mark = pass;
			SET(PASSWORD, 0);
			back = p - pass + 1;
		}
		mark = user;
		SET(USER, back);
	}
	goto st215;
st215:
	if ( ++p == pe )
		goto _test_eof215;
case 215:
#line 1000 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto tr260;
		case 35: goto tr194;
		case 37: goto tr261;
		case 47: goto tr242;
		case 48: goto tr262;
		case 49: goto tr263;
		case 50: goto tr264;
		case 58: goto st217;
		case 59: goto tr260;
		case 61: goto tr260;
		case 63: goto tr197;
		case 91: goto st40;
		case 95: goto tr260;
		case 126: goto tr260;
	}
	if ( (*p) < 51 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto tr260;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr260;
		} else if ( (*p) >= 65 )
			goto tr260;
	} else
		goto tr265;
	goto st0;
tr260:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st216;
st216:
	if ( ++p == pe )
		goto _test_eof216;
case 216:
#line 1037 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 47: goto tr251;
		case 58: goto tr268;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st216;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st216;
	} else
		goto st216;
	goto st0;
tr261:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
#line 1066 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st39;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st39;
	} else
		goto st39;
	goto st0;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st216;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st216;
	} else
		goto st216;
	goto st0;
tr268:
#line 14 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_NAME; }
	goto st217;
tr291:
#line 10 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_IPV4; }
	goto st217;
st217:
	if ( ++p == pe )
		goto _test_eof217;
case 217:
#line 1101 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 35: goto tr255;
		case 47: goto tr257;
		case 63: goto tr259;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr269;
	goto st0;
tr269:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 16 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ u->port = u->port * 10 + ((*p) - '0'); }
	goto st218;
tr272:
#line 16 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ u->port = u->port * 10 + ((*p) - '0'); }
	goto st218;
st218:
	if ( ++p == pe )
		goto _test_eof218;
case 218:
#line 1124 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 35: goto tr270;
		case 47: goto tr271;
		case 63: goto tr273;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr272;
	goto st0;
tr262:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st219;
st219:
	if ( ++p == pe )
		goto _test_eof219;
case 219:
#line 1141 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st220;
		case 47: goto tr251;
		case 58: goto tr268;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st216;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st216;
	} else
		goto st216;
	goto st0;
st220:
	if ( ++p == pe )
		goto _test_eof220;
case 220:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 47: goto tr251;
		case 48: goto st221;
		case 49: goto st234;
		case 50: goto st236;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 51 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st235;
	goto st0;
st221:
	if ( ++p == pe )
		goto _test_eof221;
case 221:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st222;
		case 47: goto tr251;
		case 58: goto tr268;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st216;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st216;
	} else
		goto st216;
	goto st0;
st222:
	if ( ++p == pe )
		goto _test_eof222;
case 222:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 47: goto tr251;
		case 48: goto st223;
		case 49: goto st230;
		case 50: goto st232;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 51 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st231;
	goto st0;
st223:
	if ( ++p == pe )
		goto _test_eof223;
case 223:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st224;
		case 47: goto tr251;
		case 58: goto tr268;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st216;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st216;
	} else
		goto st216;
	goto st0;
st224:
	if ( ++p == pe )
		goto _test_eof224;
case 224:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 47: goto tr251;
		case 48: goto st225;
		case 49: goto st226;
		case 50: goto st228;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 51 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st227;
	goto st0;
st225:
	if ( ++p == pe )
		goto _test_eof225;
case 225:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr289;
		case 37: goto st38;
		case 47: goto tr290;
		case 58: goto tr291;
		case 61: goto st216;
		case 63: goto tr292;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st216;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st216;
	} else
		goto st216;
	goto st0;
st226:
	if ( ++p == pe )
		goto _test_eof226;
case 226:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr289;
		case 37: goto st38;
		case 47: goto tr290;
		case 58: goto tr291;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr292;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st227;
	goto st0;
st227:
	if ( ++p == pe )
		goto _test_eof227;
case 227:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr289;
		case 37: goto st38;
		case 47: goto tr290;
		case 58: goto tr291;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr292;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st225;
	goto st0;
st228:
	if ( ++p == pe )
		goto _test_eof228;
case 228:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr289;
		case 37: goto st38;
		case 47: goto tr290;
		case 53: goto st229;
		case 58: goto tr291;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr292;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 46 ) {
			if ( 48 <= (*p) && (*p) <= 52 )
				goto st227;
		} else if ( (*p) >= 36 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st225;
	goto st0;
st229:
	if ( ++p == pe )
		goto _test_eof229;
case 229:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr289;
		case 37: goto st38;
		case 47: goto tr290;
		case 58: goto tr291;
		case 61: goto st216;
		case 63: goto tr292;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 46 ) {
			if ( 48 <= (*p) && (*p) <= 53 )
				goto st225;
		} else if ( (*p) >= 36 )
			goto st216;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st216;
	goto st0;
st230:
	if ( ++p == pe )
		goto _test_eof230;
case 230:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st224;
		case 47: goto tr251;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st231;
	goto st0;
st231:
	if ( ++p == pe )
		goto _test_eof231;
case 231:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st224;
		case 47: goto tr251;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st223;
	goto st0;
st232:
	if ( ++p == pe )
		goto _test_eof232;
case 232:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st224;
		case 47: goto tr251;
		case 53: goto st233;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 52 )
				goto st231;
		} else if ( (*p) >= 36 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st223;
	goto st0;
st233:
	if ( ++p == pe )
		goto _test_eof233;
case 233:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st224;
		case 47: goto tr251;
		case 58: goto tr268;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 53 )
				goto st223;
		} else if ( (*p) >= 36 )
			goto st216;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st216;
	goto st0;
st234:
	if ( ++p == pe )
		goto _test_eof234;
case 234:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st222;
		case 47: goto tr251;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st235;
	goto st0;
st235:
	if ( ++p == pe )
		goto _test_eof235;
case 235:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st222;
		case 47: goto tr251;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st221;
	goto st0;
st236:
	if ( ++p == pe )
		goto _test_eof236;
case 236:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st222;
		case 47: goto tr251;
		case 53: goto st237;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 52 )
				goto st235;
		} else if ( (*p) >= 36 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st221;
	goto st0;
st237:
	if ( ++p == pe )
		goto _test_eof237;
case 237:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st222;
		case 47: goto tr251;
		case 58: goto tr268;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 53 )
				goto st221;
		} else if ( (*p) >= 36 )
			goto st216;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st216;
	goto st0;
tr263:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st238;
st238:
	if ( ++p == pe )
		goto _test_eof238;
case 238:
#line 1700 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st220;
		case 47: goto tr251;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st239;
	goto st0;
tr265:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st239;
st239:
	if ( ++p == pe )
		goto _test_eof239;
case 239:
#line 1734 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st220;
		case 47: goto tr251;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st219;
	goto st0;
tr264:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st240;
st240:
	if ( ++p == pe )
		goto _test_eof240;
case 240:
#line 1768 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st220;
		case 47: goto tr251;
		case 53: goto st241;
		case 58: goto tr268;
		case 59: goto st216;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 52 )
				goto st239;
		} else if ( (*p) >= 36 )
			goto st216;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st219;
	goto st0;
st241:
	if ( ++p == pe )
		goto _test_eof241;
case 241:
	switch( (*p) ) {
		case 33: goto st216;
		case 35: goto tr249;
		case 37: goto st38;
		case 46: goto st220;
		case 47: goto tr251;
		case 58: goto tr268;
		case 61: goto st216;
		case 63: goto tr253;
		case 95: goto st216;
		case 126: goto st216;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 53 )
				goto st219;
		} else if ( (*p) >= 36 )
			goto st216;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st216;
		} else if ( (*p) >= 65 )
			goto st216;
	} else
		goto st216;
	goto st0;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 58: goto tr26;
		case 118: goto tr27;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr25;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr25;
	} else
		goto tr25;
	goto st0;
tr25:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st41;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
#line 1854 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) == 58 )
		goto st45;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st42;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st42;
	} else
		goto st42;
	goto st0;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	if ( (*p) == 58 )
		goto st45;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st43;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st43;
	} else
		goto st43;
	goto st0;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	if ( (*p) == 58 )
		goto st45;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st44;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st44;
	} else
		goto st44;
	goto st0;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	if ( (*p) == 58 )
		goto st45;
	goto st0;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	if ( (*p) == 58 )
		goto st163;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st46;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st46;
	} else
		goto st46;
	goto st0;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	if ( (*p) == 58 )
		goto st50;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st47;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st47;
	} else
		goto st47;
	goto st0;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	if ( (*p) == 58 )
		goto st50;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st48;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st48;
	} else
		goto st48;
	goto st0;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	if ( (*p) == 58 )
		goto st50;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st49;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st49;
	} else
		goto st49;
	goto st0;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	if ( (*p) == 58 )
		goto st50;
	goto st0;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	if ( (*p) == 58 )
		goto st149;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st51;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st51;
	} else
		goto st51;
	goto st0;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	if ( (*p) == 58 )
		goto st55;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st52;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st52;
	} else
		goto st52;
	goto st0;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	if ( (*p) == 58 )
		goto st55;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st53;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st53;
	} else
		goto st53;
	goto st0;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	if ( (*p) == 58 )
		goto st55;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st54;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st54;
	} else
		goto st54;
	goto st0;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	if ( (*p) == 58 )
		goto st55;
	goto st0;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	if ( (*p) == 58 )
		goto st135;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st56;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st56;
	} else
		goto st56;
	goto st0;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	if ( (*p) == 58 )
		goto st60;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st57;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st57;
	} else
		goto st57;
	goto st0;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	if ( (*p) == 58 )
		goto st60;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st58;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st58;
	} else
		goto st58;
	goto st0;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	if ( (*p) == 58 )
		goto st60;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st59;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st59;
	} else
		goto st59;
	goto st0;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	if ( (*p) == 58 )
		goto st60;
	goto st0;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	if ( (*p) == 58 )
		goto st121;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st61;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st61;
	} else
		goto st61;
	goto st0;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	if ( (*p) == 58 )
		goto st65;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st62;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st62;
	} else
		goto st62;
	goto st0;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	if ( (*p) == 58 )
		goto st65;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st63;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st63;
	} else
		goto st63;
	goto st0;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	if ( (*p) == 58 )
		goto st65;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st64;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st64;
	} else
		goto st64;
	goto st0;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	if ( (*p) == 58 )
		goto st65;
	goto st0;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	if ( (*p) == 58 )
		goto st107;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st66;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st66;
	} else
		goto st66;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	if ( (*p) == 58 )
		goto st70;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st67;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st67;
	} else
		goto st67;
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	if ( (*p) == 58 )
		goto st70;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st68;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st68;
	} else
		goto st68;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	if ( (*p) == 58 )
		goto st70;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st69;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st69;
	} else
		goto st69;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	if ( (*p) == 58 )
		goto st70;
	goto st0;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 48: goto st71;
		case 49: goto st98;
		case 50: goto st101;
		case 58: goto st105;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st104;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st106;
	} else
		goto st106;
	goto st0;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st93;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st90;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st90;
	} else
		goto st90;
	goto st0;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 48: goto st73;
		case 49: goto st86;
		case 50: goto st88;
	}
	if ( 51 <= (*p) && (*p) <= 57 )
		goto st87;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	if ( (*p) == 46 )
		goto st74;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 48: goto st75;
		case 49: goto st82;
		case 50: goto st84;
	}
	if ( 51 <= (*p) && (*p) <= 57 )
		goto st83;
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 46 )
		goto st76;
	goto st0;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 48: goto st77;
		case 49: goto st78;
		case 50: goto st80;
	}
	if ( 51 <= (*p) && (*p) <= 57 )
		goto st79;
	goto st0;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 93 )
		goto tr85;
	goto st0;
tr85:
#line 12 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mapped = true; }
#line 11 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = mapped ? SP_HOST_IPV4_MAPPED : SP_HOST_IPV6; }
	goto st242;
tr94:
#line 11 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = mapped ? SP_HOST_IPV4_MAPPED : SP_HOST_IPV6; }
	goto st242;
tr182:
#line 13 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_IP_FUTURE; }
	goto st242;
st242:
	if ( ++p == pe )
		goto _test_eof242;
case 242:
#line 2349 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 35: goto tr194;
		case 47: goto tr242;
		case 58: goto st217;
		case 63: goto tr197;
	}
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) == 93 )
		goto tr85;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st79;
	goto st0;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	if ( (*p) == 93 )
		goto tr85;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st77;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 53: goto st81;
		case 93: goto tr85;
	}
	if ( (*p) > 52 ) {
		if ( 54 <= (*p) && (*p) <= 57 )
			goto st77;
	} else if ( (*p) >= 48 )
		goto st79;
	goto st0;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	if ( (*p) == 93 )
		goto tr85;
	if ( 48 <= (*p) && (*p) <= 53 )
		goto st77;
	goto st0;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	if ( (*p) == 46 )
		goto st76;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st83;
	goto st0;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	if ( (*p) == 46 )
		goto st76;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st75;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 46: goto st76;
		case 53: goto st85;
	}
	if ( (*p) > 52 ) {
		if ( 54 <= (*p) && (*p) <= 57 )
			goto st75;
	} else if ( (*p) >= 48 )
		goto st83;
	goto st0;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	if ( (*p) == 46 )
		goto st76;
	if ( 48 <= (*p) && (*p) <= 53 )
		goto st75;
	goto st0;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	if ( (*p) == 46 )
		goto st74;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st87;
	goto st0;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	if ( (*p) == 46 )
		goto st74;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st73;
	goto st0;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 46: goto st74;
		case 53: goto st89;
	}
	if ( (*p) > 52 ) {
		if ( 54 <= (*p) && (*p) <= 57 )
			goto st73;
	} else if ( (*p) >= 48 )
		goto st87;
	goto st0;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	if ( (*p) == 46 )
		goto st74;
	if ( 48 <= (*p) && (*p) <= 53 )
		goto st73;
	goto st0;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	if ( (*p) == 58 )
		goto st93;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st91;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st91;
	} else
		goto st91;
	goto st0;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	if ( (*p) == 58 )
		goto st93;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st92;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st92;
	} else
		goto st92;
	goto st0;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	if ( (*p) == 58 )
		goto st93;
	goto st0;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	if ( (*p) == 58 )
		goto st97;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st94;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st94;
	} else
		goto st94;
	goto st0;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	if ( (*p) == 93 )
		goto tr94;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st95;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st95;
	} else
		goto st95;
	goto st0;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	if ( (*p) == 93 )
		goto tr94;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st96;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st96;
	} else
		goto st96;
	goto st0;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 93 )
		goto tr94;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st97;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st97;
	} else
		goto st97;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) == 93 )
		goto tr94;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st93;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st99;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st90;
	} else
		goto st90;
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st93;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st100;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st91;
	} else
		goto st91;
	goto st0;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st93;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st92;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st92;
	} else
		goto st92;
	goto st0;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	switch( (*p) ) {
		case 46: goto st72;
		case 53: goto st102;
		case 58: goto st93;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 52 )
			goto st99;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st90;
		} else if ( (*p) >= 65 )
			goto st90;
	} else
		goto st103;
	goto st0;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st93;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 53 )
			goto st100;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st91;
		} else if ( (*p) >= 65 )
			goto st91;
	} else
		goto st91;
	goto st0;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st93;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st91;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st91;
	} else
		goto st91;
	goto st0;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st93;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st103;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st90;
	} else
		goto st90;
	goto st0;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	if ( (*p) == 93 )
		goto tr94;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st94;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st94;
	} else
		goto st94;
	goto st0;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	if ( (*p) == 58 )
		goto st93;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st90;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st90;
	} else
		goto st90;
	goto st0;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	switch( (*p) ) {
		case 48: goto st108;
		case 49: goto st113;
		case 50: goto st116;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st119;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st120;
	} else
		goto st120;
	goto st0;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st109;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st109;
	} else
		goto st109;
	goto st0;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	switch( (*p) ) {
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st110;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st110;
	} else
		goto st110;
	goto st0;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	switch( (*p) ) {
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st111;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st111;
	} else
		goto st111;
	goto st0;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	switch( (*p) ) {
		case 58: goto st112;
		case 93: goto tr94;
	}
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st94;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st94;
	} else
		goto st94;
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st114;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st109;
	} else
		goto st109;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st115;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st110;
	} else
		goto st110;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st111;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st111;
	} else
		goto st111;
	goto st0;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	switch( (*p) ) {
		case 46: goto st72;
		case 53: goto st117;
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 52 )
			goto st114;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st109;
		} else if ( (*p) >= 65 )
			goto st109;
	} else
		goto st118;
	goto st0;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 53 )
			goto st115;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st110;
		} else if ( (*p) >= 65 )
			goto st110;
	} else
		goto st110;
	goto st0;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st110;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st110;
	} else
		goto st110;
	goto st0;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st118;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st109;
	} else
		goto st109;
	goto st0;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	switch( (*p) ) {
		case 58: goto st112;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st109;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st109;
	} else
		goto st109;
	goto st0;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	switch( (*p) ) {
		case 48: goto st122;
		case 49: goto st127;
		case 50: goto st130;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st133;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st134;
	} else
		goto st134;
	goto st0;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st123;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st123;
	} else
		goto st123;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	switch( (*p) ) {
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st124;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st124;
	} else
		goto st124;
	goto st0;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	switch( (*p) ) {
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st125;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st125;
	} else
		goto st125;
	goto st0;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	switch( (*p) ) {
		case 58: goto st126;
		case 93: goto tr94;
	}
	goto st0;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	switch( (*p) ) {
		case 48: goto st108;
		case 49: goto st113;
		case 50: goto st116;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st119;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st120;
	} else
		goto st120;
	goto st0;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st128;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st123;
	} else
		goto st123;
	goto st0;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st129;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st124;
	} else
		goto st124;
	goto st0;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st125;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st125;
	} else
		goto st125;
	goto st0;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	switch( (*p) ) {
		case 46: goto st72;
		case 53: goto st131;
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 52 )
			goto st128;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st123;
		} else if ( (*p) >= 65 )
			goto st123;
	} else
		goto st132;
	goto st0;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 53 )
			goto st129;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st124;
		} else if ( (*p) >= 65 )
			goto st124;
	} else
		goto st124;
	goto st0;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st124;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st124;
	} else
		goto st124;
	goto st0;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st132;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st123;
	} else
		goto st123;
	goto st0;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	switch( (*p) ) {
		case 58: goto st126;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st123;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st123;
	} else
		goto st123;
	goto st0;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	switch( (*p) ) {
		case 48: goto st136;
		case 49: goto st141;
		case 50: goto st144;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st147;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st148;
	} else
		goto st148;
	goto st0;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st137;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st137;
	} else
		goto st137;
	goto st0;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
	switch( (*p) ) {
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st138;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st138;
	} else
		goto st138;
	goto st0;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
	switch( (*p) ) {
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st139;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st139;
	} else
		goto st139;
	goto st0;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
	switch( (*p) ) {
		case 58: goto st140;
		case 93: goto tr94;
	}
	goto st0;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
	switch( (*p) ) {
		case 48: goto st122;
		case 49: goto st127;
		case 50: goto st130;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st133;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st134;
	} else
		goto st134;
	goto st0;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st142;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st137;
	} else
		goto st137;
	goto st0;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st143;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st138;
	} else
		goto st138;
	goto st0;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st139;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st139;
	} else
		goto st139;
	goto st0;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	switch( (*p) ) {
		case 46: goto st72;
		case 53: goto st145;
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 52 )
			goto st142;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st137;
		} else if ( (*p) >= 65 )
			goto st137;
	} else
		goto st146;
	goto st0;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 53 )
			goto st143;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st138;
		} else if ( (*p) >= 65 )
			goto st138;
	} else
		goto st138;
	goto st0;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st138;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st138;
	} else
		goto st138;
	goto st0;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st146;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st137;
	} else
		goto st137;
	goto st0;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	switch( (*p) ) {
		case 58: goto st140;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st137;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st137;
	} else
		goto st137;
	goto st0;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
	switch( (*p) ) {
		case 48: goto st150;
		case 49: goto st155;
		case 50: goto st158;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st161;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st162;
	} else
		goto st162;
	goto st0;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st151;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st151;
	} else
		goto st151;
	goto st0;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	switch( (*p) ) {
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st152;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st152;
	} else
		goto st152;
	goto st0;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	switch( (*p) ) {
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st153;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st153;
	} else
		goto st153;
	goto st0;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	switch( (*p) ) {
		case 58: goto st154;
		case 93: goto tr94;
	}
	goto st0;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
	switch( (*p) ) {
		case 48: goto st136;
		case 49: goto st141;
		case 50: goto st144;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st147;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st148;
	} else
		goto st148;
	goto st0;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st156;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st151;
	} else
		goto st151;
	goto st0;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st157;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st152;
	} else
		goto st152;
	goto st0;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st153;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st153;
	} else
		goto st153;
	goto st0;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
	switch( (*p) ) {
		case 46: goto st72;
		case 53: goto st159;
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 52 )
			goto st156;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st151;
		} else if ( (*p) >= 65 )
			goto st151;
	} else
		goto st160;
	goto st0;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 53 )
			goto st157;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st152;
		} else if ( (*p) >= 65 )
			goto st152;
	} else
		goto st152;
	goto st0;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st152;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st152;
	} else
		goto st152;
	goto st0;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st160;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st151;
	} else
		goto st151;
	goto st0;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
	switch( (*p) ) {
		case 58: goto st154;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st151;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st151;
	} else
		goto st151;
	goto st0;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
	switch( (*p) ) {
		case 48: goto st164;
		case 49: goto st169;
		case 50: goto st172;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st175;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st176;
	} else
		goto st176;
	goto st0;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st165;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st165;
	} else
		goto st165;
	goto st0;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
	switch( (*p) ) {
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st166;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st166;
	} else
		goto st166;
	goto st0;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
	switch( (*p) ) {
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st167;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st167;
	} else
		goto st167;
	goto st0;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
	switch( (*p) ) {
		case 58: goto st168;
		case 93: goto tr94;
	}
	goto st0;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
	switch( (*p) ) {
		case 48: goto st150;
		case 49: goto st155;
		case 50: goto st158;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st161;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st162;
	} else
		goto st162;
	goto st0;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st170;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st165;
	} else
		goto st165;
	goto st0;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st171;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st166;
	} else
		goto st166;
	goto st0;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st167;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st167;
	} else
		goto st167;
	goto st0;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
	switch( (*p) ) {
		case 46: goto st72;
		case 53: goto st173;
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 52 )
			goto st170;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st165;
		} else if ( (*p) >= 65 )
			goto st165;
	} else
		goto st174;
	goto st0;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 53 )
			goto st171;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st166;
		} else if ( (*p) >= 65 )
			goto st166;
	} else
		goto st166;
	goto st0;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st166;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st166;
	} else
		goto st166;
	goto st0;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st174;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st165;
	} else
		goto st165;
	goto st0;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
	switch( (*p) ) {
		case 58: goto st168;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st165;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st165;
	} else
		goto st165;
	goto st0;
tr26:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st177;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
#line 3983 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) == 58 )
		goto st178;
	goto st0;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
	switch( (*p) ) {
		case 48: goto st179;
		case 49: goto st184;
		case 50: goto st187;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st190;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st191;
	} else
		goto st191;
	goto st0;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st180;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st180;
	} else
		goto st180;
	goto st0;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
	switch( (*p) ) {
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st181;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st181;
	} else
		goto st181;
	goto st0;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	switch( (*p) ) {
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st182;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st182;
	} else
		goto st182;
	goto st0;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
	switch( (*p) ) {
		case 58: goto st183;
		case 93: goto tr94;
	}
	goto st0;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	switch( (*p) ) {
		case 48: goto st164;
		case 49: goto st169;
		case 50: goto st172;
	}
	if ( (*p) < 65 ) {
		if ( 51 <= (*p) && (*p) <= 57 )
			goto st175;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st176;
	} else
		goto st176;
	goto st0;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st185;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st180;
	} else
		goto st180;
	goto st0;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st186;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st181;
	} else
		goto st181;
	goto st0;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st182;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st182;
	} else
		goto st182;
	goto st0;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
	switch( (*p) ) {
		case 46: goto st72;
		case 53: goto st188;
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 52 )
			goto st185;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st180;
		} else if ( (*p) >= 65 )
			goto st180;
	} else
		goto st189;
	goto st0;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 54 ) {
		if ( 48 <= (*p) && (*p) <= 53 )
			goto st186;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 70 ) {
			if ( 97 <= (*p) && (*p) <= 102 )
				goto st181;
		} else if ( (*p) >= 65 )
			goto st181;
	} else
		goto st181;
	goto st0;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st181;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st181;
	} else
		goto st181;
	goto st0;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	switch( (*p) ) {
		case 46: goto st72;
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st189;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st180;
	} else
		goto st180;
	goto st0;
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
	switch( (*p) ) {
		case 58: goto st183;
		case 93: goto tr94;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st180;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st180;
	} else
		goto st180;
	goto st0;
tr27:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st192;
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
#line 4243 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st193;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st193;
	} else
		goto st193;
	goto st0;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
	if ( (*p) == 46 )
		goto st194;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st193;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st193;
	} else
		goto st193;
	goto st0;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
	switch( (*p) ) {
		case 33: goto st195;
		case 36: goto st195;
		case 61: goto st195;
		case 95: goto st195;
		case 126: goto st195;
	}
	if ( (*p) < 48 ) {
		if ( 38 <= (*p) && (*p) <= 46 )
			goto st195;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st195;
		} else if ( (*p) >= 65 )
			goto st195;
	} else
		goto st195;
	goto st0;
st195:
	if ( ++p == pe )
		goto _test_eof195;
case 195:
	switch( (*p) ) {
		case 33: goto st195;
		case 36: goto st195;
		case 61: goto st195;
		case 93: goto tr182;
		case 95: goto st195;
		case 126: goto st195;
	}
	if ( (*p) < 48 ) {
		if ( 38 <= (*p) && (*p) <= 46 )
			goto st195;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st195;
		} else if ( (*p) >= 65 )
			goto st195;
	} else
		goto st195;
	goto st0;
tr258:
#line 21 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ pass = p; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 16 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ u->port = u->port * 10 + ((*p) - '0'); }
	goto st243;
tr299:
#line 16 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ u->port = u->port * 10 + ((*p) - '0'); }
	goto st243;
st243:
	if ( ++p == pe )
		goto _test_eof243;
case 243:
#line 4331 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st35;
		case 35: goto tr270;
		case 37: goto st36;
		case 47: goto tr271;
		case 59: goto st35;
		case 61: goto st35;
		case 63: goto tr273;
		case 64: goto tr21;
		case 95: goto st35;
		case 126: goto st35;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st35;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st35;
		} else if ( (*p) >= 65 )
			goto st35;
	} else
		goto tr299;
	goto st0;
tr243:
#line 20 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ user = p; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st244;
st244:
	if ( ++p == pe )
		goto _test_eof244;
case 244:
#line 4366 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st245;
		case 47: goto tr251;
		case 58: goto tr252;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st213;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st213;
	} else
		goto st213;
	goto st0;
st245:
	if ( ++p == pe )
		goto _test_eof245;
case 245:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 47: goto tr251;
		case 48: goto st246;
		case 49: goto st259;
		case 50: goto st261;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 51 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st260;
	goto st0;
st246:
	if ( ++p == pe )
		goto _test_eof246;
case 246:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st247;
		case 47: goto tr251;
		case 58: goto tr252;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st213;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st213;
	} else
		goto st213;
	goto st0;
st247:
	if ( ++p == pe )
		goto _test_eof247;
case 247:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 47: goto tr251;
		case 48: goto st248;
		case 49: goto st255;
		case 50: goto st257;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 51 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st256;
	goto st0;
st248:
	if ( ++p == pe )
		goto _test_eof248;
case 248:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st249;
		case 47: goto tr251;
		case 58: goto tr252;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st213;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st213;
	} else
		goto st213;
	goto st0;
st249:
	if ( ++p == pe )
		goto _test_eof249;
case 249:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 47: goto tr251;
		case 48: goto st250;
		case 49: goto st251;
		case 50: goto st253;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 51 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st252;
	goto st0;
st250:
	if ( ++p == pe )
		goto _test_eof250;
case 250:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr289;
		case 37: goto st33;
		case 47: goto tr290;
		case 58: goto tr315;
		case 61: goto st213;
		case 63: goto tr292;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 65 ) {
		if ( 36 <= (*p) && (*p) <= 59 )
			goto st213;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st213;
	} else
		goto st213;
	goto st0;
st251:
	if ( ++p == pe )
		goto _test_eof251;
case 251:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr289;
		case 37: goto st33;
		case 47: goto tr290;
		case 58: goto tr315;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr292;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st252;
	goto st0;
st252:
	if ( ++p == pe )
		goto _test_eof252;
case 252:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr289;
		case 37: goto st33;
		case 47: goto tr290;
		case 58: goto tr315;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr292;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 46 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st250;
	goto st0;
st253:
	if ( ++p == pe )
		goto _test_eof253;
case 253:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr289;
		case 37: goto st33;
		case 47: goto tr290;
		case 53: goto st254;
		case 58: goto tr315;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr292;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 46 ) {
			if ( 48 <= (*p) && (*p) <= 52 )
				goto st252;
		} else if ( (*p) >= 36 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st250;
	goto st0;
st254:
	if ( ++p == pe )
		goto _test_eof254;
case 254:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr289;
		case 37: goto st33;
		case 47: goto tr290;
		case 58: goto tr315;
		case 61: goto st213;
		case 63: goto tr292;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 46 ) {
			if ( 48 <= (*p) && (*p) <= 53 )
				goto st250;
		} else if ( (*p) >= 36 )
			goto st213;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st213;
	goto st0;
st255:
	if ( ++p == pe )
		goto _test_eof255;
case 255:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st249;
		case 47: goto tr251;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st256;
	goto st0;
st256:
	if ( ++p == pe )
		goto _test_eof256;
case 256:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st249;
		case 47: goto tr251;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st248;
	goto st0;
st257:
	if ( ++p == pe )
		goto _test_eof257;
case 257:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st249;
		case 47: goto tr251;
		case 53: goto st258;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 52 )
				goto st256;
		} else if ( (*p) >= 36 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st248;
	goto st0;
st258:
	if ( ++p == pe )
		goto _test_eof258;
case 258:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st249;
		case 47: goto tr251;
		case 58: goto tr252;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 53 )
				goto st248;
		} else if ( (*p) >= 36 )
			goto st213;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st213;
	goto st0;
st259:
	if ( ++p == pe )
		goto _test_eof259;
case 259:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st247;
		case 47: goto tr251;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st260;
	goto st0;
st260:
	if ( ++p == pe )
		goto _test_eof260;
case 260:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st247;
		case 47: goto tr251;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st246;
	goto st0;
st261:
	if ( ++p == pe )
		goto _test_eof261;
case 261:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st247;
		case 47: goto tr251;
		case 53: goto st262;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 52 )
				goto st260;
		} else if ( (*p) >= 36 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st246;
	goto st0;
st262:
	if ( ++p == pe )
		goto _test_eof262;
case 262:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st247;
		case 47: goto tr251;
		case 58: goto tr252;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 53 )
				goto st246;
		} else if ( (*p) >= 36 )
			goto st213;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st213;
	goto st0;
tr244:
#line 20 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ user = p; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st263;
st263:
	if ( ++p == pe )
		goto _test_eof263;
case 263:
#line 4946 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st245;
		case 47: goto tr251;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st264;
	goto st0;
tr246:
#line 20 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ user = p; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st264;
st264:
	if ( ++p == pe )
		goto _test_eof264;
case 264:
#line 4983 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st245;
		case 47: goto tr251;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 48 ) {
		if ( 36 <= (*p) && (*p) <= 45 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st244;
	goto st0;
tr245:
#line 20 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ user = p; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st265;
st265:
	if ( ++p == pe )
		goto _test_eof265;
case 265:
#line 5020 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st245;
		case 47: goto tr251;
		case 53: goto st266;
		case 58: goto tr252;
		case 59: goto st213;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 52 )
				goto st264;
		} else if ( (*p) >= 36 )
			goto st213;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st244;
	goto st0;
st266:
	if ( ++p == pe )
		goto _test_eof266;
case 266:
	switch( (*p) ) {
		case 33: goto st213;
		case 35: goto tr249;
		case 37: goto st33;
		case 46: goto st245;
		case 47: goto tr251;
		case 58: goto tr252;
		case 61: goto st213;
		case 63: goto tr253;
		case 64: goto tr21;
		case 95: goto st213;
		case 126: goto st213;
	}
	if ( (*p) < 54 ) {
		if ( (*p) > 45 ) {
			if ( 48 <= (*p) && (*p) <= 53 )
				goto st244;
		} else if ( (*p) >= 36 )
			goto st213;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st213;
		} else if ( (*p) >= 65 )
			goto st213;
	} else
		goto st213;
	goto st0;
tr198:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st267;
st267:
	if ( ++p == pe )
		goto _test_eof267;
case 267:
#line 5091 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto st2;
		case -16: goto st4;
		case -12: goto st6;
		case 35: goto tr203;
		case 37: goto st15;
		case 43: goto st267;
		case 47: goto st208;
		case 58: goto tr323;
		case 63: goto tr205;
		case 92: goto st205;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -31 ) {
			if ( -64 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( (*p) > -13 ) {
				if ( 33 <= (*p) && (*p) <= 44 )
					goto st205;
			} else if ( (*p) >= -15 )
				goto st5;
		} else
			goto st3;
	} else if ( (*p) > 57 ) {
		if ( (*p) < 94 ) {
			if ( (*p) > 64 ) {
				if ( 65 <= (*p) && (*p) <= 90 )
					goto st267;
			} else if ( (*p) >= 59 )
				goto st205;
		} else if ( (*p) > 96 ) {
			if ( (*p) > 122 ) {
				if ( 123 <= (*p) && (*p) <= 126 )
					goto st205;
			} else if ( (*p) >= 97 )
				goto st267;
		} else
			goto st205;
	} else
		goto st267;
	goto st0;
tr323:
#line 9 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(SCHEME, 0); }
	goto st268;
st268:
	if ( ++p == pe )
		goto _test_eof268;
case 268:
#line 5142 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto tr325;
		case -16: goto tr327;
		case -12: goto tr329;
		case 35: goto tr194;
		case 37: goto tr331;
		case 47: goto tr196;
		case 63: goto tr197;
		case 92: goto tr330;
	}
	if ( (*p) < -15 ) {
		if ( (*p) > -33 ) {
			if ( -31 <= (*p) && (*p) <= -17 )
				goto tr326;
		} else if ( (*p) >= -64 )
			goto tr324;
	} else if ( (*p) > -13 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 126 )
				goto tr330;
		} else if ( (*p) >= 33 )
			goto tr330;
	} else
		goto tr328;
	goto st0;
tr324:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st196;
st196:
	if ( ++p == pe )
		goto _test_eof196;
case 196:
#line 5176 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st269;
	goto st0;
tr330:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st269;
st269:
	if ( ++p == pe )
		goto _test_eof269;
case 269:
#line 5188 "/Users/sbacha/siphon/build/uri_parser.c"
	switch( (*p) ) {
		case -32: goto st197;
		case -16: goto st199;
		case -12: goto st201;
		case 35: goto tr203;
		case 37: goto st202;
		case 47: goto st208;
		case 63: goto tr205;
		case 92: goto st269;
	}
	if ( (*p) < -15 ) {
		if ( (*p) > -33 ) {
			if ( -31 <= (*p) && (*p) <= -17 )
				goto st198;
		} else if ( (*p) >= -64 )
			goto st196;
	} else if ( (*p) > -13 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 126 )
				goto st269;
		} else if ( (*p) >= 33 )
			goto st269;
	} else
		goto st200;
	goto st0;
tr325:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st197;
st197:
	if ( ++p == pe )
		goto _test_eof197;
case 197:
#line 5222 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( -96 <= (*p) && (*p) <= -65 )
		goto st196;
	goto st0;
tr326:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st198;
st198:
	if ( ++p == pe )
		goto _test_eof198;
case 198:
#line 5234 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st196;
	goto st0;
tr327:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st199;
st199:
	if ( ++p == pe )
		goto _test_eof199;
case 199:
#line 5246 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( -112 <= (*p) && (*p) <= -65 )
		goto st198;
	goto st0;
tr328:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st200;
st200:
	if ( ++p == pe )
		goto _test_eof200;
case 200:
#line 5258 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -65 )
		goto st198;
	goto st0;
tr329:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st201;
st201:
	if ( ++p == pe )
		goto _test_eof201;
case 201:
#line 5270 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) <= -113 )
		goto st198;
	goto st0;
tr331:
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
	goto st202;
st202:
	if ( ++p == pe )
		goto _test_eof202;
case 202:
#line 5282 "/Users/sbacha/siphon/build/uri_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st203;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st203;
	} else
		goto st203;
	goto st0;
st203:
	if ( ++p == pe )
		goto _test_eof203;
case 203:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st269;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st269;
	} else
		goto st269;
	goto st0;
	}
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof205: cs = 205; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof206: cs = 206; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof207: cs = 207; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof208: cs = 208; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof209: cs = 209; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof210: cs = 210; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof211: cs = 211; goto _test_eof; 
	_test_eof212: cs = 212; goto _test_eof; 
	_test_eof213: cs = 213; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof214: cs = 214; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof215: cs = 215; goto _test_eof; 
	_test_eof216: cs = 216; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof217: cs = 217; goto _test_eof; 
	_test_eof218: cs = 218; goto _test_eof; 
	_test_eof219: cs = 219; goto _test_eof; 
	_test_eof220: cs = 220; goto _test_eof; 
	_test_eof221: cs = 221; goto _test_eof; 
	_test_eof222: cs = 222; goto _test_eof; 
	_test_eof223: cs = 223; goto _test_eof; 
	_test_eof224: cs = 224; goto _test_eof; 
	_test_eof225: cs = 225; goto _test_eof; 
	_test_eof226: cs = 226; goto _test_eof; 
	_test_eof227: cs = 227; goto _test_eof; 
	_test_eof228: cs = 228; goto _test_eof; 
	_test_eof229: cs = 229; goto _test_eof; 
	_test_eof230: cs = 230; goto _test_eof; 
	_test_eof231: cs = 231; goto _test_eof; 
	_test_eof232: cs = 232; goto _test_eof; 
	_test_eof233: cs = 233; goto _test_eof; 
	_test_eof234: cs = 234; goto _test_eof; 
	_test_eof235: cs = 235; goto _test_eof; 
	_test_eof236: cs = 236; goto _test_eof; 
	_test_eof237: cs = 237; goto _test_eof; 
	_test_eof238: cs = 238; goto _test_eof; 
	_test_eof239: cs = 239; goto _test_eof; 
	_test_eof240: cs = 240; goto _test_eof; 
	_test_eof241: cs = 241; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof242: cs = 242; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
	_test_eof140: cs = 140; goto _test_eof; 
	_test_eof141: cs = 141; goto _test_eof; 
	_test_eof142: cs = 142; goto _test_eof; 
	_test_eof143: cs = 143; goto _test_eof; 
	_test_eof144: cs = 144; goto _test_eof; 
	_test_eof145: cs = 145; goto _test_eof; 
	_test_eof146: cs = 146; goto _test_eof; 
	_test_eof147: cs = 147; goto _test_eof; 
	_test_eof148: cs = 148; goto _test_eof; 
	_test_eof149: cs = 149; goto _test_eof; 
	_test_eof150: cs = 150; goto _test_eof; 
	_test_eof151: cs = 151; goto _test_eof; 
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 
	_test_eof155: cs = 155; goto _test_eof; 
	_test_eof156: cs = 156; goto _test_eof; 
	_test_eof157: cs = 157; goto _test_eof; 
	_test_eof158: cs = 158; goto _test_eof; 
	_test_eof159: cs = 159; goto _test_eof; 
	_test_eof160: cs = 160; goto _test_eof; 
	_test_eof161: cs = 161; goto _test_eof; 
	_test_eof162: cs = 162; goto _test_eof; 
	_test_eof163: cs = 163; goto _test_eof; 
	_test_eof164: cs = 164; goto _test_eof; 
	_test_eof165: cs = 165; goto _test_eof; 
	_test_eof166: cs = 166; goto _test_eof; 
	_test_eof167: cs = 167; goto _test_eof; 
	_test_eof168: cs = 168; goto _test_eof; 
	_test_eof169: cs = 169; goto _test_eof; 
	_test_eof170: cs = 170; goto _test_eof; 
	_test_eof171: cs = 171; goto _test_eof; 
	_test_eof172: cs = 172; goto _test_eof; 
	_test_eof173: cs = 173; goto _test_eof; 
	_test_eof174: cs = 174; goto _test_eof; 
	_test_eof175: cs = 175; goto _test_eof; 
	_test_eof176: cs = 176; goto _test_eof; 
	_test_eof177: cs = 177; goto _test_eof; 
	_test_eof178: cs = 178; goto _test_eof; 
	_test_eof179: cs = 179; goto _test_eof; 
	_test_eof180: cs = 180; goto _test_eof; 
	_test_eof181: cs = 181; goto _test_eof; 
	_test_eof182: cs = 182; goto _test_eof; 
	_test_eof183: cs = 183; goto _test_eof; 
	_test_eof184: cs = 184; goto _test_eof; 
	_test_eof185: cs = 185; goto _test_eof; 
	_test_eof186: cs = 186; goto _test_eof; 
	_test_eof187: cs = 187; goto _test_eof; 
	_test_eof188: cs = 188; goto _test_eof; 
	_test_eof189: cs = 189; goto _test_eof; 
	_test_eof190: cs = 190; goto _test_eof; 
	_test_eof191: cs = 191; goto _test_eof; 
	_test_eof192: cs = 192; goto _test_eof; 
	_test_eof193: cs = 193; goto _test_eof; 
	_test_eof194: cs = 194; goto _test_eof; 
	_test_eof195: cs = 195; goto _test_eof; 
	_test_eof243: cs = 243; goto _test_eof; 
	_test_eof244: cs = 244; goto _test_eof; 
	_test_eof245: cs = 245; goto _test_eof; 
	_test_eof246: cs = 246; goto _test_eof; 
	_test_eof247: cs = 247; goto _test_eof; 
	_test_eof248: cs = 248; goto _test_eof; 
	_test_eof249: cs = 249; goto _test_eof; 
	_test_eof250: cs = 250; goto _test_eof; 
	_test_eof251: cs = 251; goto _test_eof; 
	_test_eof252: cs = 252; goto _test_eof; 
	_test_eof253: cs = 253; goto _test_eof; 
	_test_eof254: cs = 254; goto _test_eof; 
	_test_eof255: cs = 255; goto _test_eof; 
	_test_eof256: cs = 256; goto _test_eof; 
	_test_eof257: cs = 257; goto _test_eof; 
	_test_eof258: cs = 258; goto _test_eof; 
	_test_eof259: cs = 259; goto _test_eof; 
	_test_eof260: cs = 260; goto _test_eof; 
	_test_eof261: cs = 261; goto _test_eof; 
	_test_eof262: cs = 262; goto _test_eof; 
	_test_eof263: cs = 263; goto _test_eof; 
	_test_eof264: cs = 264; goto _test_eof; 
	_test_eof265: cs = 265; goto _test_eof; 
	_test_eof266: cs = 266; goto _test_eof; 
	_test_eof267: cs = 267; goto _test_eof; 
	_test_eof268: cs = 268; goto _test_eof; 
	_test_eof196: cs = 196; goto _test_eof; 
	_test_eof269: cs = 269; goto _test_eof; 
	_test_eof197: cs = 197; goto _test_eof; 
	_test_eof198: cs = 198; goto _test_eof; 
	_test_eof199: cs = 199; goto _test_eof; 
	_test_eof200: cs = 200; goto _test_eof; 
	_test_eof201: cs = 201; goto _test_eof; 
	_test_eof202: cs = 202; goto _test_eof; 
	_test_eof203: cs = 203; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 205: 
	case 208: 
	case 211: 
	case 267: 
	case 269: 
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	break;
	case 210: 
#line 18 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(QUERY, 0); }
	break;
	case 207: 
#line 19 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(FRAGMENT, 0); }
	break;
	case 204: 
	case 212: 
	case 215: 
	case 242: 
	case 268: 
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	break;
	case 209: 
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 18 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(QUERY, 0); }
	break;
	case 206: 
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 19 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(FRAGMENT, 0); }
	break;
	case 214: 
	case 217: 
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 15 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PORT, 0); }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	break;
	case 225: 
	case 226: 
	case 227: 
	case 228: 
	case 229: 
	case 250: 
	case 251: 
	case 252: 
	case 253: 
	case 254: 
#line 10 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_IPV4; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	break;
	case 213: 
	case 216: 
	case 219: 
	case 220: 
	case 221: 
	case 222: 
	case 223: 
	case 224: 
	case 230: 
	case 231: 
	case 232: 
	case 233: 
	case 234: 
	case 235: 
	case 236: 
	case 237: 
	case 238: 
	case 239: 
	case 240: 
	case 241: 
	case 244: 
	case 245: 
	case 246: 
	case 247: 
	case 248: 
	case 249: 
	case 255: 
	case 256: 
	case 257: 
	case 258: 
	case 259: 
	case 260: 
	case 261: 
	case 262: 
	case 263: 
	case 264: 
	case 265: 
	case 266: 
#line 14 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(HOST, 0); u->host = SP_HOST_NAME; }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	break;
	case 218: 
	case 243: 
#line 15 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PORT, 0); }
#line 8 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ mark = p; }
#line 17 "/Users/sbacha/siphon/lib/uri_parser.rl"
	{ SET(PATH, 0); }
	break;
#line 5697 "/Users/sbacha/siphon/build/uri_parser.c"
	}
	}

	_out: {}
	}

#line 186 "/Users/sbacha/siphon/lib/uri_parser.rl"
#undef SET
 
	if (cs < 204) {
		return -1 - (p - buf);
	}
	else {
		return p - buf;
	}
}

