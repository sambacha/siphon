#include "../include/siphon/ws.h"
#include "../include/siphon/error.h"
#include "../include/siphon/alloc.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include <ctype.h>

static char buffer[1024*1024];

static char *
readin (const char *path, size_t *outlen)
{
	FILE *in = stdin;
	if (path != NULL) {
		in = fopen (path, "r");
		if (in == NULL) {
			err (EXIT_FAILURE, "fopen");
		}
	}

	size_t len = fread (buffer, 1, sizeof buffer, in);
	if (len == 0) {
		err (EXIT_FAILURE, "fread");
	}

	fclose (in);

	char *copy = sp_malloc (len);
	if (copy == NULL) {
		err (EXIT_FAILURE, "sp_malloc");
	}

	memcpy (copy, buffer, len);
	*outlen = len;
	return copy;
}

int
main (int argc, char **argv)
{
	size_t len;
	char *buf = readin (argc > 1 ? argv[1] : NULL, &len);
	printf ("readin: %zu\n", len);
	char *cur = buf;
	char *end = buf + len;
	ssize_t rc = 0;

	SpWs p;
	sp_ws_init (&p);

	while (!sp_ws_is_done (&p) && cur < end) {
		rc = sp_ws_next (&p, cur, len);
		if (rc < 0) break;

		sp_ws_print_meta (&p, cur, stdout);

		if (p.type == SP_WS_PAYLOAD) {
			// write out the raw bytes
			if (p.as.masked) {
				char *m = (char *)malloc(rc);
				sp_ws_unmask (&p, m, cur, rc);
				fwrite (m, 1, rc, stdout);
				free(m);
			} else {
				fwrite (cur, 1, rc, stdout);
			}
			fflush (stdout);
		}

		cur += rc;
		len -= rc;
	}

	if (rc < 0) {
		fprintf (stderr, "ws error: %s\n", sp_strerror (rc));
	}
	return sp_alloc_summary () && rc >= 0 ? 0 : 1;
}
