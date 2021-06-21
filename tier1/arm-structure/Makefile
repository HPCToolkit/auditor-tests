OPT=-O1 -g
OBJS=libfoo.so libauditor.so main

all: test

main: main.c
	cc $(OPT) -o main main.c -Wl,-rpath,`pwd` -L. -lfoo

lib%.so: %.c
	cc $(OPT) -o $@ $< -shared -fPIC


test: $(OBJS)
	@echo running the original 'main' 
	./main
	@echo
	@echo running the audited 'main' 
	LD_AUDIT=./libauditor.so ./main

clean: 
	rm -f $(OBJS) core*
