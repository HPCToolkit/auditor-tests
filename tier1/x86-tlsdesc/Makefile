OBJS=main audit.so


run: original auditor

build: $(OBJS)

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
