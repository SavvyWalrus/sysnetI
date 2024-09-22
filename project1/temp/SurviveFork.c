#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int gval;
int main(int argc, char ** argv)
{
  int lval;
  pid_t pid;
  
  gval = 123;
  lval = 456;
  
  printf("this is the first line of output\n");
  
  pid = fork();
  if (pid < 0) {
	  printf ("unable to execute fork");
	  return;
  }
  
  if (pid > 0)
  {
    gval = lval;
    lval += 544;
	
    printf("PARENT has gval = %d\n", gval);
    printf("PARENT has lval = %d\n", lval);
  }
  else
  {
    printf("CHILD has gval = %d\n", gval);
    printf("CHILD has lval = %d\n", lval);
  }
  
  return 0;
}
