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
		int pid, cpid;
    int fd[2];
    // char buffer[256];
    char string[256];
		char numChildTemp[234];

		printf("How many machines would you like: \n");
    fgets(numChildTemp, sizeof(numChildTemp), stdin);
		int numChild = atoi(numChildTemp);
		printf("What would you like your message to be: \n");
    fgets(string, sizeof(string), stdin);

		int *pidList = (int*) malloc(numChild * sizeof(int));


    printf("Parent pid: %d\n\n", getpid());
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL)
      *pos = '\0';

    pipe(fd);

		cpid = 1;
		for (int i = 1; i <= numChild ; i++) {
			cpid = fork();
  		if(cpid){
				// parent
				close(fd[0]);
				break;
			}
			//child
			close(fd[1]);
			pidList[i-1]= getpid();
			printf("Child (%d): %d Parent: %d List at 0: %d.\n", i, getpid(), getppid(), pidList[i-1]);
		}
		wait(NULL);
		printf("Ending: %d\n", getpid());
		sleep(5);

	return(0);
}
