#define _GNU_SOURCE
#include <link.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

static void foo_wrapper(void (*foo)(int), int x) {
  foo(-x);
}

static struct wrapper_entry {
  uintptr_t* cookie;
  void (*foo)(int);
  void (*wrapper)(int);
} wrapper_table[5];

static void foo_wrapper0(int x) { return foo_wrapper(wrapper_table[0].foo, x); }
static void foo_wrapper1(int x) { return foo_wrapper(wrapper_table[1].foo, x); }
static void foo_wrapper2(int x) { return foo_wrapper(wrapper_table[2].foo, x); }
static void foo_wrapper3(int x) { return foo_wrapper(wrapper_table[3].foo, x); }

static struct wrapper_entry wrapper_table[5] = {
  {NULL, NULL, foo_wrapper0},
  {NULL, NULL, foo_wrapper1},
  {NULL, NULL, foo_wrapper2},
  {NULL, NULL, foo_wrapper3},
  {NULL, NULL, NULL},
};

unsigned int la_objopen(struct link_map* map, Lmid_t lmid, uintptr_t* cookie) {
  fprintf(stderr, "[audit] la_objopen: '%s'\n", map->l_name);
  if(strstr(map->l_name, "/libfoo.so") != NULL) {
    for(struct wrapper_entry* e = wrapper_table; ; e++) {
      if(e->wrapper == NULL) {
        fprintf(stderr, "[audit] Too many open libfoo's!\n");
        abort();
      }
      if(e->cookie == NULL) {
        e->cookie = cookie;
        break;
      }
    }
    return LA_FLG_BINDTO;
  }
  return LA_FLG_BINDFROM;
}

unsigned int la_objclose(uintptr_t* cookie) {
  fprintf(stderr, "[audit] la_objclose: '%s'\n", ((struct link_map*)*cookie)->l_name);
  for(struct wrapper_entry* e = wrapper_table; e->wrapper != NULL; e++) {
    if(cookie == e->cookie) {
      e->cookie = NULL;
      e->foo = NULL;
      break;
    }
  }
  return 0;
}

uintptr_t la_symbind64(Elf64_Sym* sym, unsigned int ndx, uintptr_t* refc, uintptr_t* defc,
                       unsigned int* flags, const char* name) {
  fprintf(stderr, "[audit] Binding symbol %s from '%s' to '%s'\n", name, ((struct link_map*)*defc)->l_name,
          ((struct link_map*)*refc)->l_name);
  if(strcmp(name, "foo") == 0) {
    struct wrapper_entry* e;
    for(e = wrapper_table; e->cookie != defc; e++) {
      if(e->wrapper == NULL) {
        fprintf(stderr, "[audit] foo defined by something that wasn't libfoo! Ignoring.\n");
        return sym->st_value;
      }
    }
    if(e->foo == NULL) {
      e->foo = (void*)sym->st_value;
    } else if(sym->st_value != (uintptr_t)e->foo) {
      fprintf(stderr, "[audit] ERROR: foo moved! was %p, now %p\n", e->foo, sym->st_value);
      abort();
    }
    return (uintptr_t)e->wrapper;
  }
  return sym->st_value;
}
