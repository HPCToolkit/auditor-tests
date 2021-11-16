.PHONY: all build-vdso build-dlinfo test-vdso test-dlinfo clean
.NOTPARALLEL:

all: build-vdso build-dlinfo test-vdso test-dlinfo

build-vdso: libauditor-vdso.so main-simple
test-vdso: build-vdso
	@echo
	@echo 'Success requires OK (not FAIL) at the end of output:'
	LD_AUDIT=./libauditor-vdso.so ./main-simple

build-dlinfo: main-dlinfo-pie main-dlinfo-nopie
test-dlinfo: build-dlinfo
	@echo
	@echo 'Success requires OK (not FAIL) at the end of output:'
	./main-dlinfo-pie
	./main-dlinfo-nopie

libauditor-vdso.so: auditor-vdso.c Makefile
	gcc -o $@ $< -fPIC -shared -ldl
main-simple: main-simple.c Makefile
	gcc -o $@ $<
main-dlinfo-pie: main-dlinfo.c Makefile
	gcc -o $@ $< -ldl -pie -fPIE
main-dlinfo-nopie: main-dlinfo.c Makefile
	gcc -o $@ $< -ldl -no-pie
