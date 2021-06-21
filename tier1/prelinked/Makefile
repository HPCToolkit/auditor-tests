OBJS = \
	main \
	main-selfaudit \
	libaudit.so

test: build original prelinked 

build: $(OBJS)

libaudit.so: libaudit.c
	gcc -o libaudit.so -fPIC -shared libaudit.c

main: main.c
	gcc -o $@ $< -ldl

main-selfaudit: main.c
	gcc -o $@ $<  -ldl -Wl,--audit=./libaudit.so

original:
	@echo
	@echo without auditor: success requires output from MAIN
	./main


prelinked:
	@echo
	@echo with prelinked auditor: success requires output from AUDITOR and MAIN
	./main-selfaudit

clean:
	rm -f $(OBJS)
