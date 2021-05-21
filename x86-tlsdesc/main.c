#include <stdio.h>
#include <dlfcn.h>

int
main(int argc, char **argv)
{
  void *handle = dlopen("libs/libmemkind.so", RTLD_LAZY);
  printf("MAIN: dolopen return code (non-zero expected): %p\n", handle);
  return (handle == 0);
}
