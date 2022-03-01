#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

static bool antirecurse = false;
static bool initted = false;
__attribute__((constructor))
static void init() {
  fprintf(stderr, "Initializing liballoc...\n");
  initted = true;
}

extern void mainfoo(bool);
extern char** environ;
static inline void check_(const char* func) {
  const char* extra = initted ? "" : " (before init)";
  if(!antirecurse) {
    antirecurse = true;
#if defined(DEATH_BY_GETENV)
#ifndef QUIET
    fprintf(stderr, "%s%s: Calling into getenv... ", func, extra);
#endif
    getenv("HOME");
#ifndef QUIET
    fprintf(stderr, "OK\n");
#endif
#elif defined(CHECK_ENVIRON)
    fprintf(stderr, "%s%s: Checking environ is present... %s\n", func, extra, environ == NULL ? "FAIL" : "OK");
#else
#error
#endif
    antirecurse = false;
  }
}
#define check() check_(__func__)

extern void* __libc_malloc(size_t);
void* malloc(size_t sz) {
  check();
  return __libc_malloc(sz);
}

extern void __libc_free(void*);
void free(void* ptr) {
  check();
  return __libc_free(ptr);
}

extern void* __libc_calloc(size_t, size_t);
void* calloc(size_t n, size_t sz) {
  check();
  return __libc_calloc(n, sz);
}

extern void* __libc_realloc(void*, size_t);
void* realloc(void* ptr, size_t sz) {
  check();
  return __libc_realloc(ptr, sz);
}

