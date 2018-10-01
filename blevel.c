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

void sigintHandler (int sigNum);

// token for passing
typedef struct {
  char input[256];
  int dst;
} token;

int main(int argc, char* argv[])
{
		int cpid;
    int fd[2];
    token tok;
    char numChildTemp[256];
    int numChild = 0;
    char destTemp[256];
    signal(SIGINT, sigintHandler);

    printf("Parent pid: %d\n\n", getpid());
    while(1){
      printf("How many machines would you like: \n");
      fgets(numChildTemp, sizeof(numChildTemp), stdin);
      printf("What would you like your message to be: \n");
      fgets(tok.input, sizeof(tok.input), stdin);
      char *pos;
      if ((pos=strchr(tok.input, '\n')) != NULL)
        *pos = '\0';
      printf("What would you like the destination of the message to be: \n");
      fgets(destTemp, sizeof(destTemp), stdin);
      tok.dst = atoi(destTemp);
      if(tok.dst == 0){
        exit(0);
      }
      numChild = atoi(numChildTemp);
      if(tok.dst > numChild){
        printf("\tThat machine doesnt exist!!!");
        exit(0);
      }
    //--------------------------------------------------------------------------
    for(int i = 1 ; i <= numChild ; i++){
      int bpid;
      pipe(fd);
      cpid = fork();
      if(cpid < 0) {
          printf("Error");
          exit(1);
      } else if (cpid == 0) { // child
          printf("Child (%d): %d Parent: %d.\n", i, getpid(), getppid());
          close(fd[1]);
          token tok2;
          read(fd[0], &tok2, sizeof(token));
          if(tok2.dst == i){
            printf("\tReceived string: %s at %d.\n", tok2.input, getpid());
            tok2.dst = 0;
            strcpy(tok.input, "");
          }
          else if(tok2.dst == 0){
            printf("\tMessage previously delivered.\n");
          }else{
            printf("\tMessage NOT delivered yet.\n");
          }
          bpid = fork();
          exit(0);
      } else  {
        close(fd[0]);
        /* Send "string" through the output side of pipe */
        write(fd[1], &tok, sizeof(token));
        wait(NULL);
      }
    }
    //--------------------------------------------------------------------------
  }
    printf("\nTHIS IS THE END\n");
  return(0);
}

void sigintHandler (int sigNum){
	exit(0);
}
