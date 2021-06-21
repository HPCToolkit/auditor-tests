#include <stdio.h>
#include <stdlib.h>

#include "timer.h"

#define AUDIT_PREFIX "LD_AUDIT=./auditor.so "
#define COMMAND "./main"

int main(int argc, char **argv) 
{
  double original, auditor;

  printf("\nTiming main without auditor:\n");
  printf("  command = '%s'\n", COMMAND);
  
  timer_start();
  system(COMMAND);
  original = timer_elapsed();
  printf("original time = %lf seconds\n", original); 

  printf("\nTiming main with auditor:\n");
  printf("  command = '%s'\n", AUDIT_PREFIX COMMAND);
  timer_start();
  system(AUDIT_PREFIX COMMAND);
  auditor = timer_elapsed();
  printf("audited time = %lf seconds\n", auditor); 

  printf("\nratio: (audited time) / (original time) = %lf\n", auditor / original); 

  return 0;
}

