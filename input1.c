/* Copyright 1994-2003 Peter Seebach
 * All wrongs reversed. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "opts.h"
#include "version.h"

/* unsort - unsort arbitrary input */

char *buffer = 0;	/* character storage */
size_t *lines = 0;	/* offsets into buffer */
int size = 0;	/* size of buffer */
int count = 0;	/* characters used in buffer */
int lcount = 0;	/* offsets used */
int lsize = 0;	/* size of offsets "array" */
char *us;		/* argv[0] or thereabouts */

static void fail(void);
static void mesg(char *, ...);
static int spew_output(int);
static int slurp_input(FILE *);

static void
fail(void) {
	free(buffer);
	free(lines);
	exit(EXIT_FAILURE);
}

/* print an identified message */
static void
mesg(char *fmt, ...) {
	va_list ap;

	fprintf(stderr, "%s: ", us);
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}

/* the astute reader will note that rand() may not be a great randomizer;
 * feel free to provide a more effective one.
 */
static int
spew_output(int nitems) {
	int i, j;
	size_t temp;

	if (nitems == 0)
		return 0;

	for (i = 0; i < nitems; ++i) {
#ifdef __bsdi__
		j = random() % nitems;
#else
		j = rand() % nitems;
#endif
		temp = lines[i];
		lines[i] = lines[j];
		lines[j] = temp;
	}

	for (i = 0; i < nitems; ++i) {
		puts(buffer + lines[i]);
	}

	return 0;
}

/* Slurp input.  Our goal is to always leave this function in a state such
 * that count refers (accurately) to the number of lines.  Lines should be
 * an allocated array of count size_t's, offsets into buffer, each `pointing'
 * to a null terminated string.
 *
 * We keep track of:
 * 1.  Current line.
 * 2.  Position in buffer.
 * 3.  Size of buffer, and of lines[].
 *
 */
static int
slurp_input(FILE *fp) {
	int c;
	int lastcount;
	size_t *tlines;
	char *tbuffer;

	if (!lines) {
		lsize = 256;
		lines = malloc(lsize * sizeof(size_t));
		if (!lines) {
			mesg("couldn't allocate memory.\n");
			fail();
		}
		lcount = 0;
	}
	if (!buffer) {
		size = 4096;
		buffer = malloc(size);
		if (!buffer) {
			mesg("couldn't allocate memory.\n");
			fail();
		}
		count = 0;
	}
	lastcount = count;
	while ((c = getc(fp)) != EOF) {
		switch (c) {
		default:
			buffer[count++] = (char) c;
			break;
		case '\n':
			buffer[count++] = '\0';
			lines[lcount++] = lastcount;
			lastcount = count;
			if (lcount >= lsize) {
				tlines = realloc(lines,
					(lsize *= 2) * sizeof(size_t));
				if (!tlines) {
					mesg("couldn't allocate memory.\n");
					fail();
				}
				lines = tlines;
			}
		}
		if (count >= size) {
			tbuffer = realloc(buffer, size *= 2);
			if (!tbuffer) {
				mesg("couldn't allocate memory.\n");
				fail();
			}
			buffer = tbuffer;
		}
	}
	buffer[count] = '\0';
	return 0;
}

int
main(int argc, char *argv[])
{
	int i, o, ret = 0;
	char *s;
	FILE *fp;

	s = argv[0];

	if ((us = strrchr(s, '/')))
		++us;
	else
		us = argv[0];

#ifdef __bsdi__
	srandom(time(NULL));
#else
	srand(time(NULL));
#endif
	while ((o = optsopt(argc, argv, "hV")) != -1) {
		switch (o) {
		case 'V':
			version();
			break;
		case 'h':	/* -h for help */
			mesg("usage: unsort [-hV] [ file ...]\n");
			exit(0);
			break;
		default:
			mesg("usage: unsort [-hV] [ file ...]\n");
			exit(EXIT_SUCCESS);
			break;
		}
	}

	if (optsind < argc) {
		for (i = optsind; i < argc; ++i) {
			if (strcmp(argv[i], "-"))
				fp = fopen(argv[i], "r");
			else
				fp = stdin;
			if (!fp) {
				mesg("couldn't open file '%s'\n", argv[i]);
				ret = EXIT_FAILURE;
			} else {
				if (slurp_input(fp))
					ret = EXIT_FAILURE;
			}
			if (fp && (fp != stdin))
				fclose(fp);
		}
	} else {
		if (slurp_input(stdin))
			ret = EXIT_FAILURE;
	}

	if (spew_output(lcount))
		ret = EXIT_FAILURE;
	return ret;
}
