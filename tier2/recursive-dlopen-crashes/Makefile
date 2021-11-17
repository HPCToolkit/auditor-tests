.PHONY: test clean
test: auditor.so auditor-wrap.so main main-wrap main-init libwrap.so libinit.so
	@echo
	@echo 'All tests below require lines end in OK (not FAIL and no error)'
	@echo
	@echo 'Outer dlopen(libwrap), inner dlopen(libinit):'
	-LD_AUDIT=./auditor.so ./main-wrap
	@echo
	@echo 'Outer libinit preloaded, inner dlopen(libinit):'
	-LD_PRELOAD=./libinit.so LD_AUDIT=./auditor.so ./main
	@echo
	@echo 'Outer libinit loaded by main dependency, inner dlopen(libinit):'
	-LD_AUDIT=./auditor.so ./main-init
	@echo
	@echo 'Outer dlopen(libinit), inner dlopen(libwrap):'
	-LD_AUDIT=./auditor-wrap.so ./main
	@echo
	@echo 'Outer dlopen(libinit), inner dlopen(libinit):'
	-LD_AUDIT=./auditor.so ./main
	@echo
	@echo 'Outer dlopen(libwrap), inner dlopen(libwrap):'
	-LD_AUDIT=./auditor-wrap.so ./main-wrap

main: main.c
	gcc -o $@ $^ -ldl
main-wrap: main.c
	gcc -o $@ $^ -ldl -DWRAPPED
main-init: main.c libinit.so
	gcc -o $@ $^ -ldl -Wl,-rpath="`realpath .`" -DDEPEND_ON_LIBINIT

auditor.so: auditor.c
	gcc -shared -fPIC -o $@ $^ -ldl
auditor-wrap.so: auditor.c
	gcc -shared -fPIC -o $@ $^ -ldl -DWRAPPED

libwrap.so: libwrap.c libinit.so
	gcc -shared -fPIC -o $@ $^ -Wl,-rpath="`realpath .`"
libinit.so: libinit.c
	gcc -shared -fPIC -o $@ $^

clean:
	rm -f main main-wrap main-init auditor.so auditor-wrap.so libwrap.so libinit.so
