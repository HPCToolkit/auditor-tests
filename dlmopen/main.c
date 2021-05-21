#include <stdio.h>

#define __USE_GNU
#include <dlfcn.h>

int main() {
	void* handle = dlmopen(LM_ID_NEWLM, "libc.so.6", RTLD_NOW);
	printf("MAIN: dlmopen succeeds\n");
}
