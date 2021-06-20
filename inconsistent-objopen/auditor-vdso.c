#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/auxv.h>
#include <string.h>

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

static bool objopen_vdso = false;
unsigned int la_objopen(struct link_map* map, Lmid_t lmid, uintptr_t* cookie) {
  printf("  la_objopen('%s')\n", map->l_name);
  if(map->l_addr == getauxval(AT_SYSINFO_EHDR)) {
    printf("    Seen vDSO from objopen!\n");
    objopen_vdso = true;
  }
  *cookie = (uintptr_t)map;
  return 0;
}

void la_preinit(uintptr_t* cookie) {
  struct link_map* link_map_vdso = NULL;
  printf("la_preinit, scanning main link_map...\n");
  for(struct link_map* map = (struct link_map*)*cookie; map != NULL; map = map->l_next) {
    printf("  l_name = '%s'\n", map->l_name);
    if(map->l_addr == getauxval(AT_SYSINFO_EHDR)) {
      printf("    Seen vDSO in link map!\n");
      link_map_vdso = map;
    }
  }

  if(link_map_vdso) {
    Dl_info info;
    dladdr((void*)link_map_vdso->l_addr + 64, &info);
    if(strcmp(info.dli_fname, link_map_vdso->l_name) == 0)
      printf("dladdr(vDSO) pathname matches link_map entry. OK.\n");
    else  printf("dladdr(vDSO) pathname differs from link_map entry. FAIL.\n");
    if(info.dli_fbase == (void*)link_map_vdso->l_addr)
      printf("dladdr(vDSO) base address matches link_map entry. OK.\n");
    else  printf("dladdr(vDSO) base address differs from link_map entry. FAIL.\n");
  }

  if(!link_map_vdso) {
    printf("vDSO unexpectedly not listed in link map. OK.\n");
  } else if(!objopen_vdso) {
    printf("vDSO listed in link map but not notified via objopen. FAIL.\n");
  } else {
    printf("vDSO notified via objopen. OK.\n");
  }
}
