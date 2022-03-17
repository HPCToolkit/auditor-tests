#include <dlfcn.h>
#include <stddef.h>
#include <stdlib.h>

static void* h = NULL;

__attribute__((constructor))
static void init() {
  h = dlopen("libfoo.so", RTLD_NOW);
}

__attribute__((destructor))
static void des() {
  dlclose(h);
}

void bar(int x) {
  void (*foo)(int) = dlsym(h, "foo");
  foo(x + (getenv("EXPECT_WRAP") ? 5 : 0));
}
