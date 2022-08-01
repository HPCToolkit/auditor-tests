#define _GNU_SOURCE
#include <link.h>
#include <string.h>
#include <stdio.h>

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

struct link_map* lib_from = NULL;
struct link_map* lib_to = NULL;
unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie) {
  char* name = rindex(map->l_name, '/');
  if(name == NULL) name = map->l_name;
  else name++;

  if(strcmp(name, "libto.so") == 0) {
    lib_to = map;
    return LA_FLG_BINDTO;
#ifdef FROM_MAIN
  } else if(name[0] == '\0') {
#else
  } else if(strcmp(name, "libfrom.so") == 0) {
#endif
    lib_from = map;
    return LA_FLG_BINDFROM;
  }
  return 0;
}

unsigned int la_objclose(uintptr_t *cookie) {
  struct link_map* map = (void*)*cookie;
  if(map == lib_from) lib_from = NULL;
  if(map == lib_to) lib_to = NULL;
  return 0;
}

uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {
  struct link_map* ref = (void*)*refcook;
  struct link_map* def = (void*)*defcook;
  printf("  la_symbind for '%s' from '%s' to '%s'... ", symname, ref->l_name, def->l_name);
  if(ref != lib_from) {
    printf("FAIL. (wrong FROM)\n");
  } else if(def != lib_to) {
    printf("FAIL. (wrong TO)\n");
  } else {
    printf("OK.\n");
  }
  return sym->st_value;
}