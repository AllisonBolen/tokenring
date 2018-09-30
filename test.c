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
          //printf("I am child PID %ld of parent %d \n", (long) getpid(), getppid());
          //printf("Child is about to fork\n");
          if((cpid = fork) < 0){
            perror("fork failed");
            exit(1);
          }else if(cpid == 0){
            wait(&status);
            printf("This is the child %d of parent %d\n", getpid(), getppid());
          }
          printf("\n---\n");
        }
      }
      else { // parent
          child = wait(&status);
          printf("Parent of all process is me: %d. we jsut heard from %d\n", getpid(), child);
      }
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
