.PHONY: all build test
.NOTPARALLEL:

all: build test
build: libauditor.so main libother.so
test: build
	@echo
	@echo 'Success requires OK (not FAIL) at the end of each line:'
	LD_AUDIT=./libauditor.so ./main

libauditor.so: auditor.c
	gcc -o $@ $< -fPIC -shared
main: main.c
	gcc -o $@ $< -ldl
libother.so: libother.c
	gcc -o $@ $< -fPIC -shared
