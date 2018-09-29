#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

void parse(char* strInput, char** parsedInput);

int main(int argc, char* argv[])
{
		int status, pid, child;
		// make fork

    for(int count = 0; count <= 2; count++){
      if ((pid = fork()) < 0) {
        perror("fork failure");
        exit(1);
      }
      // else if (pid == 0) { // child
      //     printf("I am child PID %ld\n", (long) getpid());
      //     /* insert an appropriate form of the exit() function here */
      //     exit(0);
      // }
      else { // parent
          /* insert an appropriate form of the wait() system call here */
          child = wait(&status);
          printf("Child PID %ld terminated\n", (long) child);
      }
    }
    // test commit stuff
		// pid = fork();
		// if(pid < 0){
		// 	// fork failed
		// 	perror("Fork failed\n");
		// 	exit(1);
		// }
		// else if (!pid){ // child
    //   printf("child\n");
		// 	exit(0);
		// }
		// else { // parent
		// 	waitpid(pid, &status, 0);
    //   printf("parent\n");
		// }
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
