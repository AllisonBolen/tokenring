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
// This is a c level program
int main(int argc, char* argv[])
{
		int pid, bpid, cpid;
    int fd[2];
    char buffer[256];
    char string[256];

		// make fork
    // user userInput
    printf("What would you like your message to be: \n");
    fgets(string, sizeof(string), stdin);
    //printf("Parent pid: %d\n\n", getpid());
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL)
      *pos = '\0';
    }
    pipe(fd);
    pid = fork();
    if(pid < 0) {
        printf("Error");
        exit(1);
    } else if (pid == 0) { // child
        printf("Child (%d): %d Parent: %d\n", 1, getpid(), getppid());
        close(fd[1]);
        pipe(fd);
        bpid = fork();
        if(bpid < 0) {
            printf("Error");
            exit(1);
        } else if (bpid == 0) { // child
            printf("Child (%d): %d Parent: %d\n", 2, getpid(), getppid());
            close(fd[1]);
            pipe(fd);
            cpid = fork();
            if(cpid < 0) {
                printf("Error");
                exit(1);
            } else if (cpid == 0) { // child
                printf("Child (%d): %d Parent: %d\n", 3, getpid(), getppid());
                close(fd[1]);
                // if(tok.dst == count){
                  read(fd[0], buffer, sizeof(buffer));
                  printf("Received string: '%s' at %d\n", buffer, getpid());
                exit(0);
            } else  {
              close(fd[0]);
              /* Send "string" through the output side of pipe */
              write(fd[1], string, (strlen(string)+1));
              wait(NULL);
            }
            exit(0);
        } else  {
          close(fd[0]);
          /* Send "string" through the output side of pipe */
          write(fd[1], string, (strlen(string)+1));
          wait(NULL);
        }
        exit(0);
    } else  {
      close(fd[0]);
      /* Send "string" through the output side of pipe */
      write(fd[1], string, (strlen(string)+1));
      wait(NULL);
    }
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
