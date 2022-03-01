#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>

unsigned int la_version(unsigned int v) {
  fprintf(stderr, "[audit] Loaded!\n");
  return LAV_CURRENT;
}

void la_activity(uintptr_t* cookie, unsigned int flag) {
  fprintf(stderr, "[audit] la_activity: %s\n",
          flag == LA_ACT_ADD ? "ADD" :
          flag == LA_ACT_DELETE ? "DELETE" :
          flag == LA_ACT_CONSISTENT ? "CONSISTENT" : "???");
}

unsigned int la_objopen(struct link_map* map, Lmid_t lmid, uintptr_t* cookie) {
  return LA_FLG_BINDFROM | LA_FLG_BINDTO;
}

uintptr_t la_symbind64(Elf64_Sym* sym, unsigned int idx, uintptr_t* rcook, uintptr_t* dcook, unsigned int* flags, const char* symname) {
  return sym->st_value;
}
uintptr_t la_symbind32(Elf32_Sym* sym, unsigned int idx, uintptr_t* rcook, uintptr_t* dcook, unsigned int* flags, const char* symname) {
  return sym->st_value;
}
