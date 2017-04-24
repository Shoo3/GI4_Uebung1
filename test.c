#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int global; /* In BSS segement, will automatically be assigned '0'*/

int main()
{
  int i=0;
  do{
    printf("%d\n", i);
    i++;
    if(i==3)
      exit(1);
  } while(i<5);
  return 0;
}
