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

      if ((pid = fork()) < 0) {
        perror("fork failure");
        exit(1);
      }
      else if (pid == 0) { // child
        for(int i = 0 ; i < 3; i ++){
          fork();
          printf("This is the child %d of parent %d\n", getpid(), getppid());
          wait(&status);
          printf("\n\n");

        }
      }
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
