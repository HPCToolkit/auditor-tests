#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>

unsigned int la_version(unsigned int v) {
  printf("Disabled auditor loaded!\n");
  return 0;
}
