.PHONY: all build test clean
.NOTPARALLEL:

all: build test

build: auditor2.so auditor1.so lib.so main

test: build
	@echo 'Success requires OK at the end of each line:'
	-./main
	-LD_AUDIT=./auditor1.so ./main
	-/bin/true
	-LD_AUDIT=./auditor2.so /bin/true

auditor1.so: auditor1.c
	gcc -o $@ $< -fPIC -shared

auditor2.so: auditor2.c
	gcc -o $@ $< -fPIC -ftls-model=initial-exec -shared

lib.so: lib.c
	gcc -o $@ $< -fPIC -shared

main: main.c lib.so
	gcc -o $@ $< -Wl,-rpath=`pwd` lib.so

clean:
	rm -f auditor1.so auditor2.so lib.so main
