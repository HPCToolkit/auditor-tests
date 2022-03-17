OPTS=-O2 -g

all: main auditor.so
	@echo
	@echo "Success requires OK (not FAIL):"
	LD_AUDIT=./auditor.so ./main
	@echo
	LD_BIND_NOW=1 LD_AUDIT=./auditor.so ./main

main: main.c lib.so libdelayed.so Makefile
	gcc $(OPTS) -o main main.c -Wl,-rpath="`realpath .`" lib.so -Wl,-z,now -ldl

libdelayed.so: libdelayed.c lib.so Makefile
	gcc $(OPTS) -fPIC -shared -o $@ $< -Wl,-rpath="`realpath .`" lib.so

lib.so: lib.c Makefile
	gcc $(OPTS) -fPIC -shared -o $@ $<

auditor.so: auditor.c Makefile
	gcc $(OPTS) -fPIC -shared -o $@ $<

