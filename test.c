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

      // if ((pid = fork()) < 0) {
      //   perror("fork failure");
      //   exit(1);
      // }
      // else if (pid == 0) { // child
      //   for(int i = 0 ; i < 2; i ++){
      //     fork();
      //     printf("This is the child %d of parent %d\n", getpid(), getppid());
      //     wait(&status);
      //     printf("\n\n");
      //   }
      // }
      // else { // parent
      //     child = wait(&status);
      //     printf("Parent/r of all process is me: %d. we jsut heard from %d\n", getpid(), child);
      // }
      for(int i=0;i<5;i++) // loop will run n times (n=5)
    {
        if(fork() == 0)
        {
            fork();
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            wait(NULL);
            exit(0);
        }
    }
    // for(int i=0;i<5;i++) // loop will run n times (n=5)
    // wait(NULL);
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
