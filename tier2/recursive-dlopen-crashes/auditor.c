#define _GNU_SOURCE
#include <link.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

static int libinit_status = 0;
unsigned int la_objopen(struct link_map* map, Lmid_t lm, uintptr_t* cookie) {
  if(strstr(map->l_name, "/libinit.so") != NULL) {
    fprintf(stderr, "[audit] libinit has been loaded (but not initialized)\n");
    libinit_status = 1;
  }
  return 0;
}

#ifdef WRAPPED
#define LIB "libwrap"
#define SYM "check_wrap"
#else
#define LIB "libinit"
#define SYM "check"
#endif

void la_activity(uintptr_t* cookie, unsigned int flag) {
  if(flag != LA_ACT_CONSISTENT) return;
  if(libinit_status == 1) {
    libinit_status = 2;

    fprintf(stderr, "[audit] First CONSISTENT with libinit, dlopening " LIB "...\n");
    void* h = dlmopen(LM_ID_BASE, "./" LIB ".so", RTLD_NOW);
    void (*check)(int (*)(const char*, ...)) = dlsym(h, SYM);
    fprintf(stderr, "[audit -> " LIB "] Validating libinit has initialized...\n");
    check(printf);
    dlclose(h);
  }
}
