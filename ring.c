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
    //char* output = "STRING OUTPUT";
    int fd[2];
    //char buffer[80];
    char numChildTemp[256];
    int numChild = 0;
    char destTemp[256];
		// make fork
    // user userInput
    struct token tok;
    printf("How many machines would you like: \n");
    fgets(numChildTemp, sizeof(numChildTemp), stdin);
    printf("What would you like your message to be: \n");
    fgets(tok.input, sizeof(tok.input), stdin);
    printf("What would you like the destination of the message to be: \n");
    fgets(destTemp, sizeof(destTemp), stdin);
    // convert and set
    tok.dst = atoi(destTemp);
    numChild = atoi(numChildTemp);

    for(int count = 0; count < numChild; count++){
      pipe(fd);
      if ((pid = fork()) < 0) {
        perror("fork failure");
        exit(1);
      }
      else if (pid == 0) { // child
          printf("I am child PID %ld\n", (long) getpid());
          // exit(0);
          // set up pipes between the children
          close(fd[0]);
          //write(fd[1], output, (strlen(output)+1));

      }
      else { // parent
          child = wait(&status);
          //printf("Child PID %ld terminated\n", (long) child);
          close(fd[1]);
          //read(fd[0], buffer, sizeof(buffer));
          //printf("Received string: %s at %d\n", buffer, child);
          printf("Pipe between parent %d and child %d\n", getpid(), child);
          break;
      }
      sleep(5);
    }
    printf("process");
    pause();
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
