.PHONY: test
test: main auditor.so victim.so lib-base.so lib-victim.so lib-auditor.so
	@echo
	@echo 'Running test, success requires OK (not FAIL):'
	LD_AUDIT=./auditor.so:./victim.so ./main

main: main.c
	gcc -o $@ $^
auditor.so: auditor.c
	gcc -o $@ $^ -shared -fPIC -ldl
victim.so: victim.c
	gcc -o $@ $^ -shared -fPIC -ldl
lib%.so: lib.c
	gcc -o $@ $^ -shared -fPIC
