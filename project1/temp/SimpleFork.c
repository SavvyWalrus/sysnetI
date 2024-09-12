#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
  pid_t pid;
  printf("this is the first line of output\n");
  pid = fork();
  printf("This is the second line of output from PID %d\n", pid);
  return 0;
}
