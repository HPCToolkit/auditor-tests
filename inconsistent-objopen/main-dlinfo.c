#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <link.h>
#include <string.h>

#include <elf.h>

int main() {
  Dl_info info;
  struct link_map* map;
  dladdr1(main, &info, (void*)&map, RTLD_DL_LINKMAP);
  printf("Name recorded in Dl_info:  '%s' at base %p\n", info.dli_fname, info.dli_fbase);
  printf("Name recorded in link_map: '%s' at base %p\n", map->l_name, map->l_addr);
  if(strcmp(map->l_name, info.dli_fname) == 0) printf("Pathnames match. OK.\n");
  else printf("Pathnames do not match. FAIL.\n");
  if((void*)map->l_addr == info.dli_fbase) printf("Base addresses match. OK.\n");
  else printf("Base addresses do not match. FAIL.\n");
  return 0;
}
