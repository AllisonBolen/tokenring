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
    // int fd[2];
    // char buffer[256];
     char string[256];

    printf("What would you like your message to be: \n");
    fgets(string, sizeof(string), stdin);
    printf("Parent pid: %d\n\n", getpid());
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL)
      *pos = '\0';

    // pipe(fd);
		//
		// cpid = 1;
		// for (int i = 1; i <= 3 ; i++) {
		// 	cpid = fork();
  	// 	if(cpid){
		// 		break;
		// 	}
		// 	printf("Child (%d): %d Parent: %d.\n", i, getpid(), getppid());
		// }
		// wait(NULL);
		// printf("Ending: %d\n", getpid());

		cpid = 1;
    int child_id;
    for (int i = 1; i <= 3 ; i++) {
	    if (cpid != 0) {
	        cpid = fork();
	        child_id = i;
	    }else if(cpid){
	            break;
	        }
	    }
	    if (cpid == 0) {
	        printf("Child (%d): %d Parent: %d.\n", child_id, getpid(), getppid());
	        sleep(3);
    	}
		}
    printf("Ending: %d\n", getpid());

	return(0);
}
