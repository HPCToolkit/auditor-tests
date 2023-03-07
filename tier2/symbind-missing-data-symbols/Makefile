all: libauditor.so main
	@echo 'Success requires OK at the end of each line:'
	LD_AUDIT=./libauditor.so ./main

main: main.c libdata.so libmain.so
	gcc -o $@ $< -L . -Wl,-rpath=`pwd` -ldl -ldata -lmain
libmain.so: libmain.c
	gcc -o $@ $< -fPIC -shared
libdata.so: libdata.c
	gcc -o $@ $< -fPIC -shared
libauditor.so: auditor.c
	gcc -o $@ $< -fPIC -shared
