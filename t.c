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
typedef struct {
  char input[256];
  int dst;
} token;

int main(int argc, char* argv[])
{
		int status, pid, bpid, cpid;
    int fd[2];
    char buffer[80];
    char* string = "STRING OUTPUT";
    struct token tok;
    char numChildTemp[256];
    int numChild = 0;
    char destTemp[256];

    printf("How many machines would you like: \n");
    fgets(numChildTemp, sizeof(numChildTemp), stdin);
    printf("What would you like your message to be: \n");
    fgets(tok.input, sizeof(tok.input), stdin);
    printf("What would you like the destination of the message to be: \n");
    fgets(destTemp, sizeof(destTemp), stdin);
    tok.dst = atoi(destTemp);
    numChild = atoi(numChildTemp);

    printf("Parent pid: %d\n\n", getpid());
    //--------------------------------------------------------------------------
    for(int i = 1 ; i <= numChild ; i++){
      pipe(fd);
      cpid = fork();
      if(cpid < 0) {
          printf("Error");
          exit(1);
      } else if (cpid == 0) { // child
          printf("Child (%d): %d Parent: %d\n", i, getpid(), getppid());
          close(fd[1]);
          struct token tok2;
          read(fd[0], &tok2, sizeof(token));
          if(tok2.dst == i){

            //read(fd[0], buffer, sizeof(buffer));
            printf("Received string: %s at %d\n", tok2.input, getpid());
            tok.dst = 0;
            strcpy(tok.input, "");
          }
          exit(0);
      } else  {
        close(fd[0]);
        /* Send "string" through the output side of pipe */
        write(fd[1], &tok, sizeof(token));
        wait(NULL);
      }
    }
    //--------------------------------------------------------------------------
    printf("\nTHIS IS THE END\n");
  return(0);
}
