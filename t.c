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
		int status, pid, bpid, cpid;
    int fd[2];
    char buffer[80];
    char* string = "STRING OUTPUT";
    struct token tok;
    int count =1;
    strcpy(tok.input, string);
    tok.dst = 2;
    printf("Parent pid: %d\n\n", getpid());
    //--------------------------------------------------------------------------
    for(int i = 0 ; i < 2 ; i++){
      pid = fork();
      pipe(fd);
      if(pid < 0) {
          printf("Error");
          exit(1);
      } else if (pid == 0) { // child
          printf("Child (%d): %d Parent: %d\n", count, getpid(), getppid());
          close(fd[1]);
          if(tok.dst == count){
            read(fd[0], buffer, sizeof(buffer));
            printf("Received string: %s at %d\n", buffer, getpid());
            tok.dst = 0;
            strcpy(tok.input, "");
          }
          count = count + 1;
          count = 1;
          exit(0);
      } else  {
        close(fd[0]);
        /* Send "string" through the output side of pipe */
        write(fd[1], string, (strlen(string)+1));
        wait(NULL);
      }
    }
    //--------------------------------------------------------------------------
    printf("\nTHIS IS THE END\n")
  return(0);
}
