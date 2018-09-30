#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>

void parse(char* strInput, char** parsedInput);

// token for passing
struct token{
  char input[256];
  int dst;
};

int main(int argc, char* argv[])
{
		int status, pid, cpid, child;

    printf("Parent pid: %d\n\n", getpid());

    for(i = 0; i < 5; i++) {
      pid = fork();
      if(pid < 0) {
          printf("Error");
          exit(1);
      } else if (pid == 0) {
          printf("Child (%d): %d Parent: %d\n", i + 1, getpid(), getppid());
          exit(0);
      } else  {
          wait(NULL);
      }
    }
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
