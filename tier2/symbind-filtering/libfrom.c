#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

extern void symbol();

void from() {
  printf("\nBinding symbol from libfrom.so to libto.so via PLT...\n");
  symbol();

  printf("\nBinding getenv from libfrom.so via PLT...\n");
  getenv("PATH");
}

void from_dlsym() {
  void* h = dlopen("./libto.so", RTLD_NOW);
  printf("\nBinding symbol from libfrom.so to libto.so via dlsym...\n");
  (void)dlsym(h, "symbol");
  dlclose(h);

  printf("\nBinding cos from libfrom.so via dlsym...\n");
  h = dlopen("libm.so.6", RTLD_NOW);
  (void)dlsym(h, "cos");
  dlclose(h);
}