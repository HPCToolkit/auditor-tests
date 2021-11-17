#include <stdio.h>
#include <dlfcn.h>

#ifdef WRAPPED
#define LIB "libwrap"
#define SYM "check_wrap"
#else
#define LIB "libinit"
#define SYM "check"
#endif

int main() {
  printf("[main] Dlopening " LIB "...\n");
  void* h = dlopen("./" LIB ".so", RTLD_NOW);
  void (*check)(int (*)(const char*, ...)) = dlsym(h, SYM);
  printf("[main -> " LIB "] Validating libinit has initialized...\n");
  check(printf);
  dlclose(h);
  return 0;
}

#ifdef DEPEND_ON_LIBINIT
extern void check(int (*)(const char*, ...));
void never_called() {
  check(printf);
}
#endif
