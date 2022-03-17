all: all-noaudit all-audit

all-noaudit: main-lazy main-now main-notfoo-lazy main-notfoo-now main-dl main-dlm wrap-preload.so
	./main-lazy
	./main-now
	./main-dl
	LD_PRELOAD=./wrap-preload.so EXPECT_WRAP=1 ./main-lazy
	LD_PRELOAD=./wrap-preload.so EXPECT_WRAP=1 ./main-now
	./main-dlm
	./main-notfoo-lazy
	./main-notfoo-now
	LD_PRELOAD=./wrap-preload.so EXPECT_WRAP=1 ./main-notfoo-lazy
	LD_PRELOAD=./wrap-preload.so EXPECT_WRAP=1 ./main-notfoo-now

all-audit: auditor.so main-lazy main-now main-dl main-dlm wrap-preload.so
	@echo
	LD_AUDIT=./auditor.so EXPECT_OVERRIDE=1 ./main-lazy
	@echo
	LD_AUDIT=./auditor.so EXPECT_OVERRIDE=1 ./main-now
	@echo
	LD_AUDIT=./auditor.so EXPECT_OVERRIDE=1 ./main-dl
	@echo
	LD_AUDIT=./auditor.so LD_PRELOAD=./wrap-preload.so EXPECT_OVERRIDE=1 EXPECT_WRAP=1 ./main-lazy
	@echo
	LD_AUDIT=./auditor.so LD_PRELOAD=./wrap-preload.so EXPECT_OVERRIDE=1 EXPECT_WRAP=1 ./main-now
	@echo
	LD_AUDIT=./auditor.so EXPECT_OVERRIDE=1 ./main-dlm
	@echo
	LD_AUDIT=./auditor.so EXPECT_OVERRIDE=1 ./main-notfoo-lazy
	@echo
	LD_AUDIT=./auditor.so EXPECT_OVERRIDE=1 ./main-notfoo-now
	@echo
	LD_AUDIT=./auditor.so LD_PRELOAD=./wrap-preload.so EXPECT_WRAP=1 EXPECT_OVERRIDE=1 ./main-notfoo-lazy
	@echo
	LD_AUDIT=./auditor.so LD_PRELOAD=./wrap-preload.so EXPECT_WRAP=1 EXPECT_OVERRIDE=1 ./main-notfoo-now

auditor.so: auditor.c Makefile
	gcc -o $@ $< -shared -fPIC

main-lazy: main.c libfoo.so libbar.so Makefile
	gcc -o $@ $< -L. -Wl,-rpath,`realpath .` -lfoo -lbar -Wl,-z,lazy
main-now: main.c libfoo.so libbar.so Makefile
	gcc -o $@ $< -L. -Wl,-rpath,`realpath .` -lfoo -lbar -Wl,-z,now

main-notfoo-lazy: main.c libnotfoo.so libbar.so Makefile
	gcc -o $@ $< -L. -Wl,-rpath,`realpath .` -lnotfoo -lbar -Wl,-z,lazy
main-notfoo-now: main.c libnotfoo.so libbar.so Makefile
	gcc -o $@ $< -L. -Wl,-rpath,`realpath .` -lnotfoo -lbar -Wl,-z,now

main-dl: main-dl.c libfoo.so libbar.so Makefile
	gcc -o $@ $< -L. -Wl,-rpath,`realpath .` -ldl
main-dlm: main-dl.c libfoo.so libbar.so Makefile
	gcc -o $@ $< -L. -Wl,-rpath,`realpath .` -DDLM -ldl

wrap-preload.so: wrap-preload.c Makefile
	gcc -o $@ $< -shared -fPIC -ldl

libbar.so: bar.c libfoo.so Makefile
	gcc -o $@ $< -shared -fPIC -L. -Wl,-rpath,`realpath .` -lfoo -ldl

libfoo.so: foo.c Makefile
	gcc -o $@ $< -shared -fPIC
libnotfoo.so: notfoo.c Makefile
	gcc -o $@ $< -shared -fPIC
