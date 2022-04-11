#include <stdio.h>

extern __thread int foo;

int main() {
  foo = 0;
  printf("OK\n");
  return 0;
}
