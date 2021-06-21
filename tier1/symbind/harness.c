#include <stdio.h>
#include <stdlib.h>


#define AUDIT_PREFIX "LD_AUDIT=./auditor.so "
#define COMMAND "./main"


int 
main
(
  int argc, 
  char **argv
) 
{
  double original, auditor;

  printf("\nRunning main without auditor:\n");
  printf("  command = '%s'\n", COMMAND);
  
  system(COMMAND);

  printf("\nRunning main with auditor: Success requires binding message from AUDITOR\n");
  printf("  command = '%s'\n", AUDIT_PREFIX COMMAND);
  system(AUDIT_PREFIX COMMAND);

  return 0;
}

