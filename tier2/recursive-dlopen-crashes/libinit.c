#include <stdio.h>

static int initialized = 0;
__attribute__((constructor))
static void init() {
  printf("  [libinit] Initializing... %s\n",
         initialized ? "FAIL" : "OK");
  initialized = 1;
}

void check(int (*printf)(const char*, ...)) {
  // NOTE: We use the printf from our caller instead of our own,
  // otherwise we get related but confusing segfaults.
  printf("  [libinit] Checking if initialized... %s\n",
         initialized ? "OK" : "FAIL");
}
