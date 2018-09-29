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

int main(int argc, char* argv[])
{
		int status, pid, child;
    char* output = "STRING OUTPUT";
    int fd[2];
    char buffer[80];
		// make fork

    for(int count = 0; count < 2; count++){
      pipe(fd);
      if ((pid = fork()) < 0) {
        perror("fork failure");
        exit(1);
      }
      else if (pid == 0) { // child
          printf("I am child PID %ld\n", (long) getpid());
          // exit(0);
          // set up pipes between the children and install a signal killer
          close(fd[0]);
          write(fd[1], output, (strlen(output)+1));
          child = getpid();
      }
      else { // parent
          wait(&status);
          //printf("Child PID %ld terminated\n", (long) child);
          close(fd[1]);
          read(fd[0], buffer, sizeof(buffer));
          printf("Received string: %s at %d\n", buffer, child);
      }
      sleep(5);
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
