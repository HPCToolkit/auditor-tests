.PHONY: test
test: liballoc-environ.so liballoc-getenv.so libearlymalloc.so auditor.so main
	@echo
	@echo "## Allocation functions called after init constructors in main: (expect OK not FAIL)"
	-LD_PRELOAD=./liballoc-environ.so ./main
	@echo
	@echo "## Allocation functions called before library init constructors with LD_PRELOAD: (expect OK not FAIL)"
	-LD_PRELOAD='./liballoc-environ.so ./libearlymalloc.so' ./main
	@echo
	@echo "## Allocation functions called before environ has been filled: (expect OK not FAIL)"
	-LD_PRELOAD=./liballoc-environ.so LD_AUDIT=./auditor.so ./main
	@echo
	@echo "## Versions of bash before 5.0 overload getenv and access environ without checking for NULL first: (expect no SEGV)"
	bash --version
	-LD_PRELOAD=./liballoc-getenv.so LD_AUDIT=./auditor.so bash -c 'exit 0'

liballoc.so: alloc.c Makefile
	gcc -o $@ $< -shared -fPIC
libearlymalloc.so: earlymalloc.c Makefile
	gcc -o $@ $< -shared -fPIC
liballoc-environ.so: alloc.c Makefile
	gcc -o $@ $< -shared -fPIC -DCHECK_ENVIRON
liballoc-getenv.so: alloc.c Makefile
	gcc -o $@ $< -shared -fPIC -DDEATH_BY_GETENV -DQUIET
auditor.so: auditor.c Makefile
	gcc -o $@ $< -shared -fPIC
main: main.c Makefile
	gcc -o $@ $<
