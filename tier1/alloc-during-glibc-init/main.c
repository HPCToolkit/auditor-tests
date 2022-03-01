#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor))
static void init() {
  fprintf(stderr, "Initializing main...\n");
}

int main() {
  free(malloc(12));
  return 0;
}
