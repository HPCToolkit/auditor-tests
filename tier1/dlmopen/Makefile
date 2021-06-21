OBJS = \
	main \
	libaudit.so


test: build original preloaded

build: $(OBJS)

libaudit.so: libaudit.c
	gcc -o libaudit.so -fPIC -shared libaudit.c

main: main.c
	gcc -o $@ $< -ldl

original:
	@echo
	@echo standalone program: success =  output from MAIN
	./main

preloaded:
	@echo
	@echo test preloaded auditor: success requires output from AUDITOR and MAIN 
	LD_AUDIT=./libaudit.so ./main

clean:
	rm -f $(OBJS)
