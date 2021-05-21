#include <stdio.h>

#define __USE_GNU
#include <dlfcn.h>

int main() {
	void* handle = dlopen("libc.so.6", RTLD_NOW);
	printf("MAIN: dlopen succeeds\n");
}
