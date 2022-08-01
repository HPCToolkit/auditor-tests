#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

extern void symbol();
extern void from();
extern void from_dlsym();

int main() {
  from();

  printf("\nBinding symbol from main to libto.so via PLT...\n");
  symbol();

  printf("\nBinding getenv from main via PLT...\n");
  getenv("PATH");

  from_dlsym();

  void* h = dlopen("./libto.so", RTLD_NOW);
  printf("\nBinding symbol from main to libto.so via dlsym...\n");
  (void)dlsym(h, "symbol");
  dlclose(h);

  printf("\nBinding cos from main via dlsym...\n");
  h = dlopen("libm.so.6", RTLD_NOW);
  (void)dlsym(h, "cos");
  dlclose(h);

  return 0;
}