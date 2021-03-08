
#line 1 "/Users/sbacha/siphon/lib/http/cache_control.rl"
#include "siphon/http.h"

#include <assert.h>


#line 55 "/Users/sbacha/siphon/lib/http/cache_control.rl"


ssize_t
sp_cache_control_parse (SpCacheControl *cc, const char *buf, size_t len)
{
	assert (cc != NULL);
	assert (buf != NULL);

	memset (cc, 0, sizeof *cc);

	const char *restrict p = buf;
	const char *restrict pe = p + len;
	const char *restrict eof = pe;
	int64_t neg = 1;
	uint64_t num = 0;
	SpRange16 str = { 0, 0 };
	bool val = false;
	int cs = 1;

#define SET(n) do { cc->type |= SP_CACHE_##n; } while (0)
#define SETNUM(n, key) do {       \
	SET(n);                       \
	cc->key = neg * (int64_t)num; \
	num = 0;                      \
	neg = 1;                      \
	val = false;                  \
} while (0)
#define SETSTR(n, key) do {       \
	SET(n);                       \
	cc->key = str;                \
	str.off = 0;                  \
	str.len = 0;                  \
	val = false;                  \
} while (0)
	
#line 45 "/Users/sbacha/siphon/build/http_cache_control.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr41:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr57:
#line 12 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(MAX_AGE, max_age); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr64:
#line 20 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{
		SET(MAX_STALE);
		if (val) {
			SETNUM(MAX_STALE_TIME, max_stale);
		}
	}
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr80:
#line 14 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(MIN_FRESH, min_fresh); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr96:
#line 17 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(MUST_REVALIDATE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr107:
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr111:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
	goto st1;
tr113:
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
	goto st1;
tr119:
#line 11 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(NO_STORE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr129:
#line 15 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(NO_TRANSFORM); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr144:
#line 16 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(ONLY_IF_CACHED); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr154:
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr158:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
	goto st1;
tr160:
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
	goto st1;
tr175:
#line 18 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(PROXY_REVALIDATE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr181:
#line 8 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(PUBLIC); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
tr193:
#line 13 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(S_MAXAGE, s_maxage); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 156 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto st1;
		case 33: goto tr2;
		case 77: goto tr3;
		case 78: goto tr4;
		case 79: goto tr5;
		case 80: goto tr6;
		case 83: goto tr7;
		case 109: goto tr3;
		case 110: goto tr4;
		case 111: goto tr5;
		case 112: goto tr6;
		case 115: goto tr7;
		case 124: goto tr2;
		case 126: goto tr2;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < 35 ) {
			if ( 9 <= (*p) && (*p) <= 13 )
				goto st1;
		} else if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr2;
		} else
			goto tr2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto tr2;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr2;
		} else
			goto tr2;
	} else
		goto tr2;
	goto st0;
st0:
cs = 0;
	goto _out;
tr2:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 205 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr39:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr56:
#line 12 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(MAX_AGE, max_age); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr63:
#line 20 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{
		SET(MAX_STALE);
		if (val) {
			SETNUM(MAX_STALE_TIME, max_stale);
		}
	}
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr79:
#line 14 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(MIN_FRESH, min_fresh); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr95:
#line 17 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(MUST_REVALIDATE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr106:
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr109:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
	goto st2;
tr112:
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
	goto st2;
tr118:
#line 11 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(NO_STORE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr128:
#line 15 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(NO_TRANSFORM); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr143:
#line 16 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(ONLY_IF_CACHED); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr153:
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr156:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
	goto st2;
tr159:
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
	goto st2;
tr174:
#line 18 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(PROXY_REVALIDATE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr180:
#line 8 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(PUBLIC); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
tr192:
#line 13 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(S_MAXAGE, s_maxage); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 338 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto st2;
		case 44: goto st1;
		case 59: goto st1;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st2;
	goto st0;
tr42:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 355 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 34: goto st4;
		case 124: goto tr9;
		case 126: goto tr9;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr9;
		} else if ( (*p) >= 33 )
			goto tr9;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto tr9;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr9;
		} else
			goto tr9;
	} else
		goto tr9;
	goto st0;
tr9:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 387 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st17;
		case 44: goto tr41;
		case 59: goto tr41;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 34 )
		goto tr12;
	goto tr11;
tr11:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 429 "/Users/sbacha/siphon/build/http_cache_control.c"
	if ( (*p) == 34 )
		goto tr14;
	goto st5;
tr12:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st18;
tr14:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 447 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto st2;
		case 44: goto st1;
		case 59: goto st1;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st2;
	goto st0;
tr3:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 464 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st20;
		case 73: goto st37;
		case 85: goto st48;
		case 97: goto st20;
		case 105: goto st37;
		case 117: goto st48;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 88: goto st21;
		case 120: goto st21;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 45: goto st22;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st23;
		case 83: goto st29;
		case 97: goto st23;
		case 115: goto st29;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 71: goto st24;
		case 103: goto st24;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st25;
		case 101: goto st25;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr53;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr53:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 703 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 34: goto st4;
		case 45: goto tr15;
		case 46: goto tr9;
		case 48: goto tr16;
		case 58: goto tr9;
		case 124: goto tr9;
		case 126: goto tr9;
	}
	if ( (*p) < 49 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr9;
		} else if ( (*p) >= 33 )
			goto tr9;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr9;
		} else if ( (*p) >= 64 )
			goto tr9;
	} else
		goto tr17;
	goto st0;
tr15:
#line 29 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ neg = -1; }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 738 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st17;
		case 44: goto tr41;
		case 48: goto tr54;
		case 58: goto st17;
		case 59: goto tr41;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 49 <= (*p) && (*p) <= 57 )
				goto tr55;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr16:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st27;
tr54:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st27;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
#line 785 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr56;
		case 33: goto st17;
		case 44: goto tr57;
		case 59: goto tr57;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr56;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr17:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st28;
tr55:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st28;
tr58:
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 834 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr56;
		case 33: goto st17;
		case 44: goto tr57;
		case 58: goto st17;
		case 59: goto tr57;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr56;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr58;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 84: goto st30;
		case 116: goto st30;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st31;
		case 97: goto st31;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 76: goto st32;
		case 108: goto st32;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st33;
		case 101: goto st33;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 32: goto tr63;
		case 33: goto st16;
		case 44: goto tr64;
		case 59: goto tr64;
		case 61: goto tr65;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr63;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr65:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 1033 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 34: goto st4;
		case 45: goto tr18;
		case 46: goto tr9;
		case 48: goto tr19;
		case 58: goto tr9;
		case 124: goto tr9;
		case 126: goto tr9;
	}
	if ( (*p) < 49 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr9;
		} else if ( (*p) >= 33 )
			goto tr9;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr9;
		} else if ( (*p) >= 64 )
			goto tr9;
	} else
		goto tr20;
	goto st0;
tr18:
#line 29 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ neg = -1; }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
#line 1068 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st17;
		case 44: goto tr41;
		case 48: goto tr66;
		case 58: goto st17;
		case 59: goto tr41;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 49 <= (*p) && (*p) <= 57 )
				goto tr67;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr19:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st35;
tr66:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st35;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
#line 1115 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr63;
		case 33: goto st17;
		case 44: goto tr64;
		case 59: goto tr64;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr63;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr20:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st36;
tr67:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st36;
tr68:
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 1164 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr63;
		case 33: goto st17;
		case 44: goto tr64;
		case 58: goto st17;
		case 59: goto tr64;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr63;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr68;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 78: goto st38;
		case 110: goto st38;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 45: goto st39;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 70: goto st40;
		case 102: goto st40;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 82: goto st41;
		case 114: goto st41;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st42;
		case 101: goto st42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 83: goto st43;
		case 115: goto st43;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 72: goto st44;
		case 104: goto st44;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr76;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr76:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 1461 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 34: goto st4;
		case 45: goto tr21;
		case 46: goto tr9;
		case 48: goto tr22;
		case 58: goto tr9;
		case 124: goto tr9;
		case 126: goto tr9;
	}
	if ( (*p) < 49 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr9;
		} else if ( (*p) >= 33 )
			goto tr9;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr9;
		} else if ( (*p) >= 64 )
			goto tr9;
	} else
		goto tr23;
	goto st0;
tr21:
#line 29 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ neg = -1; }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st45;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
#line 1496 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st17;
		case 44: goto tr41;
		case 48: goto tr77;
		case 58: goto st17;
		case 59: goto tr41;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 49 <= (*p) && (*p) <= 57 )
				goto tr78;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr22:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st46;
tr77:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st46;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
#line 1543 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr79;
		case 33: goto st17;
		case 44: goto tr80;
		case 59: goto tr80;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr79;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr23:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st47;
tr78:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st47;
tr81:
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st47;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
#line 1592 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr79;
		case 33: goto st17;
		case 44: goto tr80;
		case 58: goto st17;
		case 59: goto tr80;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr79;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr81;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 83: goto st49;
		case 115: goto st49;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 84: goto st50;
		case 116: goto st50;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 45: goto st51;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 82: goto st52;
		case 114: goto st52;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st53;
		case 101: goto st53;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 86: goto st54;
		case 118: goto st54;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st55;
		case 97: goto st55;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 76: goto st56;
		case 108: goto st56;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 73: goto st57;
		case 105: goto st57;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 68: goto st58;
		case 100: goto st58;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st59;
		case 97: goto st59;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 84: goto st60;
		case 116: goto st60;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st61;
		case 101: goto st61;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 32: goto tr95;
		case 33: goto st16;
		case 44: goto tr96;
		case 59: goto tr96;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr95;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr4:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st62;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
#line 2087 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 79: goto st63;
		case 111: goto st63;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 45: goto st64;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 67: goto st65;
		case 83: goto st72;
		case 84: goto st77;
		case 99: goto st65;
		case 115: goto st72;
		case 116: goto st77;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st66;
		case 97: goto st66;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 67: goto st67;
		case 99: goto st67;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 72: goto st68;
		case 104: goto st68;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st69;
		case 101: goto st69;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 32: goto tr106;
		case 33: goto st16;
		case 44: goto tr107;
		case 59: goto tr107;
		case 61: goto tr108;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr106;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr108:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 2357 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 34: goto st10;
		case 124: goto tr24;
		case 126: goto tr24;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr24;
		} else if ( (*p) >= 33 )
			goto tr24;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto tr24;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr24;
		} else
			goto tr24;
	} else
		goto tr24;
	goto st0;
tr24:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st70;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
#line 2389 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr109;
		case 33: goto st70;
		case 44: goto tr111;
		case 59: goto tr111;
		case 124: goto st70;
		case 126: goto st70;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st70;
		} else if ( (*p) >= 9 )
			goto tr109;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st70;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st70;
		} else
			goto st70;
	} else
		goto st70;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 34 )
		goto tr27;
	goto tr26;
tr26:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 2431 "/Users/sbacha/siphon/build/http_cache_control.c"
	if ( (*p) == 34 )
		goto tr29;
	goto st11;
tr27:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st71;
tr29:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st71;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
#line 2449 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr112;
		case 44: goto tr113;
		case 59: goto tr113;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr112;
	goto st0;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 84: goto st73;
		case 116: goto st73;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 79: goto st74;
		case 111: goto st74;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 82: goto st75;
		case 114: goto st75;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st76;
		case 101: goto st76;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 32: goto tr118;
		case 33: goto st16;
		case 44: goto tr119;
		case 59: goto tr119;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr118;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 82: goto st78;
		case 114: goto st78;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st79;
		case 97: goto st79;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 78: goto st80;
		case 110: goto st80;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 83: goto st81;
		case 115: goto st81;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 70: goto st82;
		case 102: goto st82;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 79: goto st83;
		case 111: goto st83;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 82: goto st84;
		case 114: goto st84;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 77: goto st85;
		case 109: goto st85;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 32: goto tr128;
		case 33: goto st16;
		case 44: goto tr129;
		case 59: goto tr129;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr128;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr5:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st86;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
#line 2924 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 78: goto st87;
		case 110: goto st87;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 76: goto st88;
		case 108: goto st88;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 89: goto st89;
		case 121: goto st89;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 45: goto st90;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 73: goto st91;
		case 105: goto st91;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 70: goto st92;
		case 102: goto st92;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 45: goto st93;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 67: goto st94;
		case 99: goto st94;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st95;
		case 97: goto st95;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 67: goto st96;
		case 99: goto st96;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 72: goto st97;
		case 104: goto st97;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st98;
		case 101: goto st98;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 68: goto st99;
		case 100: goto st99;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 32: goto tr143;
		case 33: goto st16;
		case 44: goto tr144;
		case 59: goto tr144;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr143;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr6:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st100;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
#line 3387 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 82: goto st101;
		case 85: goto st123;
		case 114: goto st101;
		case 117: goto st123;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 73: goto st102;
		case 79: goto st109;
		case 105: goto st102;
		case 111: goto st109;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 86: goto st103;
		case 118: goto st103;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st104;
		case 97: goto st104;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 84: goto st105;
		case 116: goto st105;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st106;
		case 101: goto st106;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	switch( (*p) ) {
		case 32: goto tr153;
		case 33: goto st16;
		case 44: goto tr154;
		case 59: goto tr154;
		case 61: goto tr155;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr153;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr155:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 3625 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 34: goto st13;
		case 124: goto tr30;
		case 126: goto tr30;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr30;
		} else if ( (*p) >= 33 )
			goto tr30;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto tr30;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr30;
		} else
			goto tr30;
	} else
		goto tr30;
	goto st0;
tr30:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st107;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
#line 3657 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr156;
		case 33: goto st107;
		case 44: goto tr158;
		case 59: goto tr158;
		case 124: goto st107;
		case 126: goto st107;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st107;
		} else if ( (*p) >= 9 )
			goto tr156;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st107;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st107;
		} else
			goto st107;
	} else
		goto st107;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 34 )
		goto tr33;
	goto tr32;
tr32:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 3699 "/Users/sbacha/siphon/build/http_cache_control.c"
	if ( (*p) == 34 )
		goto tr35;
	goto st14;
tr33:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st108;
tr35:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st108;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
#line 3717 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr159;
		case 44: goto tr160;
		case 59: goto tr160;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr159;
	goto st0;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 88: goto st110;
		case 120: goto st110;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 89: goto st111;
		case 121: goto st111;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 45: goto st112;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 82: goto st113;
		case 114: goto st113;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st114;
		case 101: goto st114;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 86: goto st115;
		case 118: goto st115;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st116;
		case 97: goto st116;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 76: goto st117;
		case 108: goto st117;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 73: goto st118;
		case 105: goto st118;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 68: goto st119;
		case 100: goto st119;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st120;
		case 97: goto st120;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 84: goto st121;
		case 116: goto st121;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st122;
		case 101: goto st122;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	switch( (*p) ) {
		case 32: goto tr174;
		case 33: goto st16;
		case 44: goto tr175;
		case 59: goto tr175;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr174;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 66: goto st124;
		case 98: goto st124;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 76: goto st125;
		case 108: goto st125;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 73: goto st126;
		case 105: goto st126;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 67: goto st127;
		case 99: goto st127;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	switch( (*p) ) {
		case 32: goto tr180;
		case 33: goto st16;
		case 44: goto tr181;
		case 59: goto tr181;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr180;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr7:
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st128;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
#line 4356 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 45: goto st129;
		case 59: goto tr41;
		case 61: goto tr42;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 77: goto st130;
		case 109: goto st130;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st131;
		case 97: goto st131;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 88: goto st132;
		case 120: goto st132;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 65: goto st133;
		case 97: goto st133;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 71: goto st134;
		case 103: goto st134;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr42;
		case 69: goto st135;
		case 101: goto st135;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st16;
		case 44: goto tr41;
		case 59: goto tr41;
		case 61: goto tr189;
		case 124: goto st16;
		case 126: goto st16;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st16;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st16;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st16;
		} else
			goto st16;
	} else
		goto st16;
	goto st0;
tr189:
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 4622 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 34: goto st4;
		case 45: goto tr36;
		case 46: goto tr9;
		case 48: goto tr37;
		case 58: goto tr9;
		case 124: goto tr9;
		case 126: goto tr9;
	}
	if ( (*p) < 49 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr9;
		} else if ( (*p) >= 33 )
			goto tr9;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr9;
		} else if ( (*p) >= 64 )
			goto tr9;
	} else
		goto tr38;
	goto st0;
tr36:
#line 29 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ neg = -1; }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 4657 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr39;
		case 33: goto st17;
		case 44: goto tr41;
		case 48: goto tr190;
		case 58: goto st17;
		case 59: goto tr41;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 49 <= (*p) && (*p) <= 57 )
				goto tr191;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr37:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st137;
tr190:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st137;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
#line 4704 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr192;
		case 33: goto st17;
		case 44: goto tr193;
		case 59: goto tr193;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr192;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 58 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr38:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
#line 27 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.off = p - buf; }
	goto st138;
tr191:
#line 36 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ val = true; }
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st138;
tr194:
#line 30 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ num = num*10 + ((*p)-'0'); }
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 4753 "/Users/sbacha/siphon/build/http_cache_control.c"
	switch( (*p) ) {
		case 32: goto tr192;
		case 33: goto st17;
		case 44: goto tr193;
		case 58: goto st17;
		case 59: goto tr193;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 42 ) {
		if ( (*p) > 13 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st17;
		} else if ( (*p) >= 9 )
			goto tr192;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 64 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr194;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
	}
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
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
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
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
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
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
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 108: 
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
	break;
	case 71: 
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
	break;
	case 16: 
	case 17: 
	case 19: 
	case 20: 
	case 21: 
	case 22: 
	case 23: 
	case 24: 
	case 25: 
	case 26: 
	case 29: 
	case 30: 
	case 31: 
	case 32: 
	case 34: 
	case 37: 
	case 38: 
	case 39: 
	case 40: 
	case 41: 
	case 42: 
	case 43: 
	case 44: 
	case 45: 
	case 48: 
	case 49: 
	case 50: 
	case 51: 
	case 52: 
	case 53: 
	case 54: 
	case 55: 
	case 56: 
	case 57: 
	case 58: 
	case 59: 
	case 60: 
	case 62: 
	case 63: 
	case 64: 
	case 65: 
	case 66: 
	case 67: 
	case 68: 
	case 72: 
	case 73: 
	case 74: 
	case 75: 
	case 77: 
	case 78: 
	case 79: 
	case 80: 
	case 81: 
	case 82: 
	case 83: 
	case 84: 
	case 86: 
	case 87: 
	case 88: 
	case 89: 
	case 90: 
	case 91: 
	case 92: 
	case 93: 
	case 94: 
	case 95: 
	case 96: 
	case 97: 
	case 98: 
	case 100: 
	case 101: 
	case 102: 
	case 103: 
	case 104: 
	case 105: 
	case 109: 
	case 110: 
	case 111: 
	case 112: 
	case 113: 
	case 114: 
	case 115: 
	case 116: 
	case 117: 
	case 118: 
	case 119: 
	case 120: 
	case 121: 
	case 123: 
	case 124: 
	case 125: 
	case 126: 
	case 128: 
	case 129: 
	case 130: 
	case 131: 
	case 132: 
	case 133: 
	case 134: 
	case 135: 
	case 136: 
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 127: 
#line 8 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(PUBLIC); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 106: 
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 69: 
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 76: 
#line 11 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(NO_STORE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 27: 
	case 28: 
#line 12 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(MAX_AGE, max_age); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 137: 
	case 138: 
#line 13 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(S_MAXAGE, s_maxage); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 46: 
	case 47: 
#line 14 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETNUM(MIN_FRESH, min_fresh); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 85: 
#line 15 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(NO_TRANSFORM); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 99: 
#line 16 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(ONLY_IF_CACHED); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 61: 
#line 17 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(MUST_REVALIDATE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 122: 
#line 18 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SET(PROXY_REVALIDATE); }
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 33: 
	case 35: 
	case 36: 
#line 20 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{
		SET(MAX_STALE);
		if (val) {
			SETNUM(MAX_STALE_TIME, max_stale);
		}
	}
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
	break;
	case 107: 
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
#line 9 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(PRIVATE, private); }
	break;
	case 70: 
#line 28 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ str.len = (p - buf) - str.off; }
#line 10 "/Users/sbacha/siphon/lib/http/cache_control.rl"
	{ SETSTR(NO_CACHE, no_cache); }
	break;
#line 5131 "/Users/sbacha/siphon/build/http_cache_control.c"
	}
	}

	_out: {}
	}

#line 90 "/Users/sbacha/siphon/lib/http/cache_control.rl"

	if (cs < 16) {
		return -1 - (p - buf);
	}
	else {
		return p - buf;
	}
}

