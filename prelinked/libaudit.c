#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>

unsigned int la_version(unsigned int version) {
	fprintf(stderr, "AUDITOR: enter la_version\n");
	return LAV_CURRENT;
}
