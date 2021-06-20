#define _GNU_SOURCE
#include <link.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

static bool first = true;
void la_activity(uintptr_t* cookie, unsigned int flag) {
  if(flag == LA_ACT_CONSISTENT && first) {
    first = false;
#ifdef DLMOPEN
    fprintf(stderr, "  Attempting to dlmopen(LM_ID_BASE, nonexistent.so) at la_activity(LA_ACT_CONSISTENT)... ");
    dlmopen(LM_ID_BASE, "/nonexistent.so", RTLD_NOW);
#else
    fprintf(stderr, "  Attempting to dlopen(nonexistent.so) at la_activity(LA_ACT_CONSISTENT)... ");
    dlopen("/nonexistent.so", RTLD_NOW);
#endif
    fprintf(stderr, "OK.\n");
  }
}
