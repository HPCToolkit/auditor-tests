OBJS=main audit.so


run: precheck original auditor

build: $(OBJS)

precheck:
	!(ldd libs/* | grep 'not found')

auditor: build
	LD_AUDIT=./audit.so ./main

original: build
	./main

audit.so: audit.c
	gcc -o $@ -shared -fPIC $<

main: main.c
	gcc -o $@ -g $< -ldl

clean:
	rm -rf $(OBJS) *core*
