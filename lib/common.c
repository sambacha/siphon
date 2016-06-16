#include "../include/siphon/common.h"
#include "../include/siphon/fmt.h"

const uint64_t SP_POWER_OF_2_PRIMES[64] = {
	1ULL, 2ULL, 3ULL,
	7ULL, 13ULL, 31ULL,
	61ULL, 127ULL, 251ULL,
	509ULL, 1021ULL, 2039ULL,
	4093ULL, 8191ULL, 16381ULL,
	32749ULL, 65521ULL, 131071ULL,
	262139ULL, 524287ULL, 1048573ULL,
	2097143ULL, 4194301ULL, 8388593ULL,
	16777213ULL, 33554393ULL, 67108859ULL,
	134217689ULL, 268435399ULL, 536870909ULL,
	1073741789ULL, 2147483647ULL, 4294967291ULL,
	8589934583ULL, 17179869143ULL, 34359738337ULL,
	68719476731ULL, 137438953447ULL, 274877906899ULL,
	549755813881ULL, 1099511627689ULL, 2199023255531ULL,
	4398046511093ULL, 8796093022151ULL, 17592186044399ULL,
	35184372088777ULL, 70368744177643ULL, 140737488355213ULL,
	281474976710597ULL, 562949953421231ULL, 1125899906842597ULL,
	2251799813685119ULL, 4503599627370449ULL, 9007199254740881ULL,
	18014398509481951ULL, 36028797018963913ULL, 72057594037927931ULL,
	144115188075855859ULL, 288230376151711717ULL, 576460752303423433ULL,
	1152921504606846883ULL, 2305843009213693951ULL, 4611686018427387847ULL,
	9223372036854775783ULL,
};

void
sp_print_ptr (const void *val, FILE *out)
{
	fprintf (out, "%p", val);
}

void
sp_print_str (const void *val, FILE *out)
{
	sp_fmt_str (out, val, strlen (val), true);
}

