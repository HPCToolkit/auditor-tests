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

struct link_map* base_head = NULL;
void la_activity(uintptr_t* cookie, unsigned int flag) {
  if(*cookie > 2) {
    struct link_map* m = (void*)*cookie;
    *cookie = 1;
    printf("  la_activity('%s', LA_ACT_%s), cookie %p now = %lu\n",
           name(m),
           flag == LA_ACT_CONSISTENT ? "CONSISTENT" :
           flag == LA_ACT_ADD ? "ADD" : "DELETE",
           cookie, (unsigned long)*cookie);
  }
}

unsigned int la_objopen(struct link_map* m, Lmid_t lmid, uintptr_t* cookie) {
  *cookie = 2;
  printf("  la_objopen('%s', lmid: %d), cookie %p now = %lu\n",
         name(m), (int)lmid, cookie, (unsigned long)*cookie);
  return 0;
}

unsigned int la_objclose(uintptr_t* cookie) {
  if(*cookie > 2) {
    printf("  la_objclose('%s')... FAIL. (cookie unset)\n", name((void*)*cookie));
  } else if(*cookie == 1) {
    printf("  la_objclose(%p)... FAIL. (cookie not seen by objopen)\n", cookie);
  } else {
    printf("  la_objclose(%p)... OK.\n", cookie);
  }
  return 0;
}
