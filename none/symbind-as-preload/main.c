#include <stdio.h>

extern void foo(int);
extern void bar(int);

int main() {
  foo(9);
  bar(9);
  return 0;
}
