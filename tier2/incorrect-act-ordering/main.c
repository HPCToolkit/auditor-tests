#include <stdio.h>
#include <dlfcn.h>

int main() {
  printf("Calling dlopen(libgood.so)...\n");
  void* h = dlopen("./libgood.so", RTLD_NOW);
  printf("Calling dlclose(libgood.so)...\n");
  dlclose(h);
  printf("Calling dlopen(libbad.so)...\n");
  dlopen("./libbad.so", RTLD_NOW);
  printf("Exiting...\n");
  return 0;
}
