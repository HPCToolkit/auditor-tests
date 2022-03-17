#include <stdio.h>
#include <stdlib.h>

void foo(int x) {
  int absx = x < 0 ? -x : x;
  printf("notfoo(%d)... %s... %s\n", x,
    (absx > 10) == (getenv("EXPECT_WRAP") != NULL) ? "OK" : "FAIL",
    x > 0 ? "OK" : "FAIL");
}
