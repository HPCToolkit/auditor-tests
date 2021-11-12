#define _GNU_SOURCE
#include <link.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int la_version(unsigned int v) { return LAV_CURRENT; }

void la_preinit(uintptr_t* cookie) {
  // Call some PLT functions in libc
  void* x = malloc(42);
  free(x);

  void* h;
  h = dlmopen(LM_ID_BASE, "./lib-base.so", RTLD_NOW);
  dlsym(h, "foo");
  dlclose(h);
  h = dlopen("./lib-victim.so", RTLD_NOW);
  dlsym(h, "foo");
  dlclose(h);
}
