#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

void foo(int x) {
  void (*realfoo)(int) = dlsym(RTLD_NEXT, "foo");
  realfoo(x + 5);
}
