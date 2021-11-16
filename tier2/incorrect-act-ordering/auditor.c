#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>
#include <sys/auxv.h>

static const char* name(struct link_map* m) {
  if(m->l_name[0] == '\0')
    return (const char*)getauxval(AT_EXECFN);
  return m->l_name;
}

unsigned int la_version(unsigned int v) {
  return LAV_CURRENT;
}

unsigned int state = 42;  // Something that isn't an LA_ACT_* constant
struct link_map* base_head = NULL;
void la_activity(uintptr_t* cookie, unsigned int flag) {
  state = flag;
  if(((struct link_map*)*cookie) == base_head) {
    printf("  la_activity(LA_ACT_%s)\n", flag == LA_ACT_CONSISTENT ? "CONSISTENT" :
                                         flag == LA_ACT_ADD ? "ADD" : "DELETE");
  } else {
    printf("  la_activity([not LM_ID_BASE], LA_ACT_%s)\n", flag == LA_ACT_CONSISTENT ? "CONSISTENT" :
                                                           flag == LA_ACT_ADD ? "ADD" : "DELETE");
  }
}

unsigned int la_objopen(struct link_map* m, Lmid_t lmid, uintptr_t* cookie) {
  if(lmid == LM_ID_BASE)
    for(base_head = m; base_head->l_prev != NULL; base_head = base_head->l_prev);
  printf("  la_objopen('%s')... ", name(m));
  if(state == LA_ACT_ADD)
    printf("OK.\n");
  else
    printf("FAIL. (in state %s)\n",
           state == LA_ACT_CONSISTENT ? "LA_ACT_CONSISTENT" :
           state == LA_ACT_DELETE ? "LA_ACT_DELETE" : "[initial]");
  *cookie = (uintptr_t)m;
  return 0;
}

unsigned int la_objclose(uintptr_t* cookie) {
  struct link_map* m = (void*)*cookie;
  printf("  la_objclose('%s')... ", name(m));
  if(state == LA_ACT_DELETE)
    printf("OK.\n");
  else
    printf("FAIL. (in state %s)\n",
           state == LA_ACT_CONSISTENT ? "LA_ACT_CONSISTENT" :
           state == LA_ACT_ADD ? "LA_ACT_ADD" : "[initial]");
  return 0;
}
