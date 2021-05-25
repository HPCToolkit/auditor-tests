#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <link.h>
#include <stdio.h>
#include <string.h>


static void 
announce
(
  const char *symname
)
{
  printf("AUDITOR: binding %s\n", symname);
  if (strcmp(symname, "bind_test") == 0) printf("AUDITOR: binding %s\n", symname);
}


unsigned int 
la_version
(
  unsigned int version
)
{
  printf("AUDITOR: la_version %d\n", version);
  return version;
}


uintptr_t la_symbind32
(
  Elf32_Sym *sym, unsigned int ndx,
  uintptr_t *refcook, 
  uintptr_t *defcook,
  unsigned int *flags, 
  const char *symname
)
{
  announce(symname);
  return sym->st_value;
}


uintptr_t la_symbind64
(
  Elf64_Sym *sym, unsigned int ndx,
  uintptr_t *refcook, 
  uintptr_t *defcook,
  unsigned int *flags, 
  const char *symname
) 
{
  announce(symname);
  return sym->st_value;
}                

unsigned int 
la_objopen
(
  struct link_map* map, 
  Lmid_t lmid, 
  uintptr_t* cookie
)
{
  return LA_FLG_BINDFROM | LA_FLG_BINDTO;
}
