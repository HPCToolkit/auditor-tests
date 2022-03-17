#include <dlfcn.h>

// PLT callee
extern void bind_test();

int main(int argc, char **argv) 
{
  bind_test();

  void* h = dlopen("libdelayed.so", RTLD_NOW);
  void (*delayed_bind_test)() = dlsym(h, "delayed_bind_test");
  delayed_bind_test();

  return 0;
}

