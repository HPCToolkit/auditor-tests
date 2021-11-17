#include <dlfcn.h>
#include <stdio.h>

// From libinit.so
extern void check(int (*)(const char*, ...));

void check_wrap(int (*printf)(const char*, ...)) {
  printf("[libwrap -> libinit] Passing validation down to libinit...\n");
  return check(printf);
}
