#define _GNU_SOURCE
#include <dlfcn.h>
#include <stddef.h>

#ifdef DLM
#define dlopen(name, flags) dlmopen(LM_ID_NEWLM, name, flags)
#endif

int main() {
  void* h = dlopen("libfoo.so", RTLD_NOW);
  void (*foo)(int) = dlsym(h, "foo");
  foo(9);
  dlclose(h);

  h = dlopen("libbar.so", RTLD_NOW);
  foo = dlsym(h, "bar");
  foo(9);

  h = dlopen("libfoo.so", RTLD_NOW);
  foo = dlsym(h, "foo");
  foo(9);
}
