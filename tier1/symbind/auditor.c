#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>
#include <string.h>

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

unsigned int la_objopen(struct link_map* map, Lmid_t lmid, uintptr_t* cookie) {
  *cookie = (map->l_prev == NULL && lmid == LM_ID_BASE) ? 1 : 0;
  return LA_FLG_BINDFROM | LA_FLG_BINDTO;
}

static unsigned int cnt = 0;
static void symbind(const char *symname) {
  if(strcmp(symname, "bind_test") == 0) {
    cnt++;
    printf("[audit] Observing binding of symbol %s\n", symname);
  }
}
uintptr_t la_symbind32(Elf32_Sym *sym, unsigned int ndx, uintptr_t *refcook,
                       uintptr_t *defcook, unsigned int *flags, const char *symname) {
  symbind(symname);
  return sym->st_value;
}
uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook,
                       uintptr_t *defcook, unsigned int *flags, const char *symname) {
  symbind(symname);
  return sym->st_value;
}

unsigned int la_objclose(uintptr_t* cookie) {
  if(*cookie) {
    printf("End of program, saw %u bindings... %s\n", cnt, cnt == 2 ? "OK" : "FAIL");
  }
}
