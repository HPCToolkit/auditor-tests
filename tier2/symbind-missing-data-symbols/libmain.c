#include <stdio.h>

extern char data_symbol;
extern char function_symbol();

void libmain() {
  printf("\nBinding data symbol from lib to libdata.so...\n");
  char d = data_symbol;
  printf("Value: '%c' == 'O'......... %s.\n", d, d == 'O' ? "OK" : "FAIL");

  printf("\nBinding function symbol as data from lib to libdata.so...\n");
  char (*f)() = &function_symbol;
  d = f();
  printf("Value: %p -> '%c' == 'O'... %s.\n", f, d, d == 'O' ? "OK" : "FAIL");
}
