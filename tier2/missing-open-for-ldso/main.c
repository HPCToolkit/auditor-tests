#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

int main() {
  printf("Calling dlmopen(libother.so) [1]...\n");
  void* h1 = dlmopen(LM_ID_NEWLM, "./libother.so", RTLD_NOW);
  printf("Calling dlmopen(libother.so) [2]...\n");
  void* h2 = dlmopen(LM_ID_NEWLM, "./libother.so", RTLD_NOW);
  printf("Calling dlmopen(libother.so) [3]...\n");
  void* h3 = dlmopen(LM_ID_NEWLM, "./libother.so", RTLD_NOW);
  printf("Calling dlclose([1])...\n");
  dlclose(h1);
  printf("Calling dlclose([2])...\n");
  dlclose(h2);
  printf("Calling dlclose([3])...\n");
  dlclose(h3);
  printf("Exiting...\n");
  return 0;
}
