#include <stdio.h>

extern void lib_good();

void lib_bad() {
  lib_good();
}
