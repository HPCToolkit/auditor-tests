#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>

__thread char buffer[4096];
__thread int used;

unsigned int la_version(unsigned int v) {
  used = 0;
  printf("OK\n");
  return LAV_CURRENT;
}
