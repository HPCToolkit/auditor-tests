OBJS = \
	lib.so \
	auditor.so \
	harness \
	main

OPTS=-O2 -g


test: build run

build: $(OBJS)

run:
	./harness

main: main.c lib.so
	gcc $(OPTS) -o main main.c -Wl,-rpath=`pwd` lib.so

harness: harness.c 
	gcc $(OPTS) -o $@ $<

%.so: %.c
	gcc $(OPTS) -fPIC -shared -o $@ $<

clean:
	/bin/rm -rf $(OBJS) 
