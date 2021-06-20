#define _GNU_SOURCE
#include <link.h>
#include <dlfcn.h>
#include <stdio.h>

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

void la_preinit(uintptr_t* cookie) {
#ifdef DLMOPEN
  fprintf(stderr, "  Attempting to dlmopen(LM_ID_BASE, nonexistent.so) at la_preinit... ");
  dlmopen(LM_ID_BASE, "/nonexistent.so", RTLD_NOW);
#else
  fprintf(stderr, "  Attempting to dlopen(nonexistent.so) at la_preinit... ");
  dlopen("/nonexistent.so", RTLD_NOW);
#endif
  fprintf(stderr, "OK.\n");
}
