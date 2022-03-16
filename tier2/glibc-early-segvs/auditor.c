#define _GNU_SOURCE
#include <assert.h>
#include <link.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>
#include <error.h>
#include <signal.h>
#include <stdarg.h>
#include <ctype.h>
#include <dlfcn.h>

#ifdef DIE_FROM_ISSPACE
volatile int out;
static inline void might_die() {
  out = isspace(' ');
}
#elif DIE_FROM_GETHOSTID
volatile long out;
static inline void might_die() {
  out = gethostid();
}
#elif DIE_FROM_DLOPEN
static inline void might_die() {
  void* h = dlopen("./lib.so", RTLD_NOW);
  dlclose(h);
}
#elif DIE_FROM_DLINFO
static struct link_map* module = NULL;
static inline void might_die() {
  if(module == NULL) {
    printf("SKIP... ");
    return;
  }
  Lmid_t x;
  dlinfo(module, RTLD_DI_LMID, &x);
}
#elif DIE_FROM_DLADDR
static inline void might_die() {
  Dl_info info;
  dladdr(la_version, &info);
}
#else
#error One of the DIE_* flags needs to be set on the compile line!
#endif

static sigjmp_buf jump_target;
static void jump(int _) {
  siglongjmp(jump_target, 1);
}
static void attempt_call() {
  struct sigaction old;
  if(sigsetjmp(jump_target, 1) == 0) {
    struct sigaction ours = { .sa_handler = jump, .sa_flags = 0, };
    sigaction(SIGSEGV, &ours, &old);
    might_die();
    printf("OK.\n");
  } else {
    printf("FAIL. (segv caught)\n");
  }
  sigaction(SIGSEGV, &old, NULL);
}

unsigned int la_version(unsigned int v) {
  printf("  Attempting call during la_version... ");
  attempt_call();
  return LAV_CURRENT;
}

unsigned int la_objopen(struct link_map* map, Lmid_t lmid, uintptr_t* cookie) {
#ifdef DIE_FROM_DLINFO
  module = map;
#endif
  printf("  Attempting call during la_objopen of '%s'... ", map->l_name);
  attempt_call();
  *cookie = (uintptr_t)map;
  return 0;
}

void la_activity(uintptr_t* cookie, unsigned int flag) {
  printf("  Attempting call during la_activity(%s)... ",
         flag == LA_ACT_CONSISTENT ? "LA_ACT_CONSISTENT" :
         flag == LA_ACT_ADD ? "LA_ACT_ADD" :
         flag == LA_ACT_DELETE ? "LA_ACT_DELETE" : "????");
  attempt_call();
}

void la_preinit(uintptr_t* cookie) {
  printf("  Attempting call during la_preinit... ");
  attempt_call();
}
