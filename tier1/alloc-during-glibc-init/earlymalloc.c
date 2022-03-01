#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor))
static void init() {
  fprintf(stderr, "Calling malloc early...\n");
  void* x = malloc(12);
}
