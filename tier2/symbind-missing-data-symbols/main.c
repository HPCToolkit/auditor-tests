#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

extern char data_symbol;
extern char function_symbol();

extern void libmain();

int main() {
  printf("\nBinding data symbol from main to libdata.so...\n");
  char d = data_symbol;
  printf("Value: '%c' == 'O'......... %s.\n", d, d == 'O' ? "OK" : "FAIL");

  printf("\nBinding function symbol as data from main to libdata.so...\n");
  char (*f)() = &function_symbol;
  d = f();
  printf("Value: %p -> '%c' == 'O'... %s.\n", f, d, d == 'O' ? "OK" : "FAIL");

  libmain();

  void* h = dlopen("./libdata.so", RTLD_NOW);

  printf("\nBinding data symbol from main to libdata.so via dlsym...\n");
  d = *(char*)dlsym(h, "data_symbol");
  printf("Value: '%c' == 'O'......... %s.\n", d, d == 'O' ? "OK" : "FAIL");

  printf("\nBinding function symbol as data from main to libdata.so via dlsym...\n");
  f = dlsym(h, "function_symbol");
  d = f();
  printf("Value: %p -> '%c' == 'O'... %s.\n", f, d, d == 'O' ? "OK" : "FAIL");

  dlclose(h);

  return 0;
}
