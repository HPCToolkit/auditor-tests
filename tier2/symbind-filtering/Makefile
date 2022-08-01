all: libauditor.so libauditor-frommain.so main
	@echo 'Success requires OK at the end of each line:'
	LD_AUDIT=./libauditor.so ./main
	@echo
	LD_AUDIT=./libauditor-frommain.so ./main

main: main.c libfrom.so libto.so
	gcc -o $@ $< -L . -Wl,-rpath=`pwd` -Wl,-z,lazy -ldl -lfrom -lto
libfrom.so: libfrom.c libto.so
	gcc -o $@ $< -fPIC -shared -L . -Wl,-rpath=`pwd` -Wl,-z,lazy -lto
libto.so: libto.c
	gcc -o $@ $< -fPIC -shared
libauditor.so: auditor.c
	gcc -o $@ $< -fPIC -shared
libauditor-frommain.so: auditor.c
	gcc -o $@ $< -fPIC -shared -DFROM_MAIN
