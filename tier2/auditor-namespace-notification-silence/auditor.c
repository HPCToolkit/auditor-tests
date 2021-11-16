#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>
#include <string.h>

unsigned int la_version(unsigned int v) { return LAV_CURRENT; }

enum bits { bit_search = 1, bit_open = 2, bit_close = 4 };
enum bits victim = 0, base = 0, lib = 0;
char* la_objsearch(const char* name, uintptr_t* cookie, unsigned int flag) {
  if(strcmp(name, "./victim.so") == 0) victim |= bit_search;
  else if(strcmp(name, "./lib-base.so") == 0) base |= bit_search;
  else if(strcmp(name, "./lib-victim.so") == 0) lib |= bit_search;
  else return (char*)name;
  // If a binary we care about,
  fprintf(stderr, "[audit] la_objsearch for %s, OK.\n", name);
  return (char*)name;
}
unsigned int la_objopen(struct link_map* map, Lmid_t lm, uintptr_t* cookie) {
  *cookie = (uintptr_t)map;
  if(strcmp(map->l_name, "./victim.so") == 0) victim |= bit_open;
  else if(strcmp(map->l_name, "./lib-base.so") == 0) base |= bit_open;
  else if(strcmp(map->l_name, "./lib-victim.so") == 0) lib |= bit_open;
  else return LA_FLG_BINDTO | LA_FLG_BINDFROM;
  // If a binary we care about,
  fprintf(stderr, "[audit] la_objopen for %s, OK.\n", map->l_name);
  return LA_FLG_BINDTO | LA_FLG_BINDFROM;
}
unsigned int la_objclose(uintptr_t* cookie) {
  struct link_map* map = (void*)*cookie;
  if(strcmp(map->l_name, "./victim.so") == 0) victim |= bit_close;
  else if(strcmp(map->l_name, "./lib-base.so") == 0) base |= bit_close;
  else if(strcmp(map->l_name, "./lib-victim.so") == 0) lib |= bit_close;
  else return 0;
  // If a binary we care about,
  fprintf(stderr, "[audit] la_objclose for %s, OK.\n", map->l_name);
  return 0;
}

int symbound = 0;
uintptr_t la_symbind64(Elf64_Sym* sym, unsigned int ndx, uintptr_t* refc,
                       uintptr_t* defc, unsigned int* flags, const char* name) {
  struct link_map* refmap = (void*)*refc;
  if(strcmp(refmap->l_name, "./victim.so") == 0) {
    fprintf(stderr, "[audit] Unexpected call to la_symbind for %s from %s, FAIL.\n", name, refmap->l_name);
    symbound = 1;
  }
  return sym->st_value;
}
uintptr_t la_symbind32(Elf32_Sym* sym, unsigned int ndx, uintptr_t* refc,
                       uintptr_t* defc, unsigned int* flags, const char* name) {
  struct link_map* refmap = (void*)*refc;
  if(strcmp(refmap->l_name, "./victim.so") == 0) {
    fprintf(stderr, "[audit] Unexpected call to la_symbind for %s -> %s, FAIL.\n", name, refmap->l_name);
    symbound = 1;
  }
  return sym->st_value;
}

static void check(int status, const char* soname) {
  if((status & bit_search) == 0)
    fprintf(stderr, "[audit] Expected la_objsearch for %s, FAIL.\n", soname);
  if((status & bit_open) == 0)
    fprintf(stderr, "[audit] Expected la_objopen for %s, FAIL.\n", soname);
  if((status & bit_close) == 0)
    fprintf(stderr, "[audit] Expected la_objclose for %s, FAIL.\n", soname);
}
__attribute__((destructor))
static void end() {
  fprintf(stderr, "\n");
  if(!symbound) fprintf(stderr, "[audit] No la_symbind calls for ./victim.so, OK.\n");
  check(victim, "victim.so");
  check(base, "lib-base.so");
  check(lib, "lib-victim.so");
}
