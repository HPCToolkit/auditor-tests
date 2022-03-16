.PHONY: all build build-% test test-% clean
.SECONDARY:
.NOTPARALLEL:

causes_of_death := isspace gethostid dlopen dladdr dlinfo
all: build test
build: $(foreach c,$(causes_of_death),build-$(c))
test: $(foreach c,$(causes_of_death),test-$(c))

build-%: libauditor-%.so lib.so main
	@true
test-%: build-%
	@echo
	@echo 'Death by $*, success requires OK at the end of each line:'
	LD_AUDIT=./libauditor-$*.so ./main

DIEFLAG_isspace := -DDIE_FROM_ISSPACE
DIEFLAG_gethostid := -DDIE_FROM_GETHOSTID
DIEFLAG_dlopen := -DDIE_FROM_DLOPEN
DIEFLAG_dladdr := -DDIE_FROM_DLADDR
DIEFLAG_dlinfo := -DDIE_FROM_DLINFO
libauditor-%.so: auditor.c Makefile
	gcc -o $@ $(DIEFLAG_$*) $(COLOR_FLAG) -fPIC -shared $< -ldl -g

main: main.c Makefile
	gcc -o $@ $< -ldl
lib.so: lib.c Makefile
	gcc -o $@ $< -fPIC -shared

clean:
	rm -f libauditor-*.so main
