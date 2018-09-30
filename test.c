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
		int status, pid, child;
    int fd[2];
    char buffer[80];
    char numChildTemp[256];
    int numChild = 0;
    char destTemp[256];
    printf("Parent pid: %d\n\n", getpid());

      if ((pid = fork()) < 0) {
        perror("fork failure");
        exit(1);
      }
      else if (pid == 0) { // child
        for(int i = 0 ; i < 2; i ++){
          printf("I am child PID %ld of parent %d \n", (long) getpid(), getppid());
          printf("Child is about to fork\n");
          int childpid = fork();
          printf("This is the child %d of parent %d\n", getpid(), getppid());
          printf("\n\n new loop \n\n");
        }
      }
      else { // parent
          child = wait(&status);
          printf("parent of all process is me: %d\n", getpid());
      }
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}