.PHONY: all build test clean
.NOTPARALLEL:

all: build test
build: libdisabledauditor.so libemptyauditor.so main main-disabledauditor
test: build
	@echo
	@echo 'Success requires both "Disabled auditor loaded!" and OK in the output:'
	-LD_AUDIT=./libemptyauditor.so:./libdisabledauditor.so ./main
	-LD_AUDIT=./libemptyauditor.so ./main-disabledauditor

libdisabledauditor.so: disabledauditor.c
	gcc -o $@ $< -fPIC -shared
libemptyauditor.so: emptyauditor.c
	gcc -o $@ $< -fPIC -shared
main: main.c
	gcc -o $@ $<
main-disabledauditor: main.c
	gcc -o $@ $< -Wl,--audit=./libdisabledauditor.so

clean:
	rm -f libdisabledauditor.so libemptyauditor.so main main-disabledauditor
