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
    pipe
		// make fork
    // user userInput
    printf("What would you like your message to be: \n");
    fgets(string, sizeof(string), stdin);
    printf("Parent pid: %d\n\n", getpid());
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL)
      *pos = '\0';


    for(int n = 0; n < 3; n++){

    }
    pipe(fd);
    for(int i = 0; i < 3; i++){
    pid = fork();
    if(pid < 0) {
        printf("Error");
        exit(1);
    } else if (pid == 0) { // child
        printf("Child (%d): %d Parent: %d\n", n, getpid(), getppid());
        // close(fd[1]);
        // read(fd[0], buffer, sizeof(buffer));
        //printf("%s\n", buffer);
    } else  {
      // close(fd[0]);
      // /* Send "string" through the output side of pipe */
      // write(fd[1], string, (strlen(string)+1));
      wait(NULL);
    }
  }
	return(0);
}
