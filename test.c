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
    printf("Parent pid: %d\n\n", getpid());
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL)
      *pos = '\0';

    pipe(fd);

		cpid = 1;
		for (int i =0; i < 3 ; i++) {
  		if (cpid != 0) {
    		cpid = fork();
				printf("Child (%d): %d Parent: %d Message: %s Dst: %d.\n", i, getpid(), getppid());
  		}
		}


	return(0);
}
