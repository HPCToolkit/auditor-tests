#define _GNU_SOURCE
#include <link.h>
#include <string.h>
#include <stdio.h>

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie) {
  return LA_FLG_BINDTO | LA_FLG_BINDFROM;
}

static char data_override = 'O';
static char function_override() { return 'O'; }

uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {
  struct link_map* ref = (void*)*refcook;
  struct link_map* def = (void*)*defcook;
  printf("  la_symbind for '%s' from '%s' to '%s'", symname, ref->l_name, def->l_name);
  if(strcmp(symname, "data_symbol") == 0) {
    printf(", overriding.\n");
    return (uintptr_t)(void*)&data_override;
  }
  if(strcmp(symname, "function_symbol") == 0) {
    printf(", overriding.\n");
    return (uintptr_t)(void*)&function_override;
  }
  printf(".\n");
  return sym->st_value;
}
