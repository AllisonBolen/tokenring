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
    char buffer[80];
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

    //for(int count = 0; count < numChild; count++){
      pipe(fd);
      close(fd[0])
      printf("writing to pipe??\n");
      write(fd[1], tok.input, (strlen(tok.input)+1));

      if ((pid = fork()) < 0) {
        perror("fork failure");
        exit(1);
      }
      else if (pid == 0) { // child
          printf("I am child PID %ld\n", (long) getpid());
          // set up pipes between the children
          close(fd[1]);
          printf("Reading from pipe??\n");
          read(fd[0], buffer, sizeof(buffer));
          printf("Received string: %s at %d\n", buffer, child);
      }
      else { // parent
          child = wait(&status);
          // set up pipe to read from parent?
          //close(fd[0]);
          printf("Pipe between parent %d and child %d\n", getpid(), child);
          // printf("writing to pipe??\n");
          // write(fd[1], tok.input, (strlen(tok.input)+1));
      }
      sleep(5);
    //}
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
