.PHONY: all build test clean
.NOTPARALLEL:

all: build test
build: libauditor-activity.so libauditor-m-activity.so libauditor-preinit.so libauditor-m-preinit.so main
test: build
	@echo 'Success requires OK at the end of each line:'
	-LD_AUDIT=./libauditor-activity.so ./main
	-LD_AUDIT=./libauditor-m-activity.so ./main
	-LD_AUDIT=./libauditor-preinit.so ./main
	-LD_AUDIT=./libauditor-m-preinit.so ./main

libauditor-activity.so: auditor-activity.c
	gcc -o $@ $< -ldl -fPIC -shared
libauditor-preinit.so: auditor-preinit.c
	gcc -o $@ $< -ldl -fPIC -shared
libauditor-m-activity.so: auditor-activity.c
	gcc -o $@ -DDLMOPEN $< -ldl -fPIC -shared
libauditor-m-preinit.so: auditor-preinit.c
	gcc -o $@ -DDLMOPEN $< -ldl -fPIC -shared
main: main.c
	gcc -o $@ $<

clean:
	rm -f libauditor.so lib.so main
