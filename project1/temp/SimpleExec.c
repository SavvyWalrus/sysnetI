#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int gval;
int main(int argc, char ** argv)
{
  int lval;
  pid_t pid;
  
  gval = 9;
  lval = 0;
  
  printf("this is the first line of output\n");
  
  pid = fork();
  if (pid != 0)
  {
    execl("./slow", NULL);
    printf("Child says 'Hello!'\n");
  }
  else
  {
    gval = lval;
    lval += 100;
    printf("PARENT has gval = %d\n", gval);
    printf("PARENT has lval = %d\n", lval);
  }
  
  return 0;
}
