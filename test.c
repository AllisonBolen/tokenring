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
int *pidList;
typedef struct {
  char input[256];
  int dst;
} token;
void sigintHandler (int sigNum);

#define WRITE 1
#define READ 0

int main(int argc, char* argv[])
{
		int pid;
    int fd[2];
    // char buffer[256];
		token tok;
    char numChildTemp[256];
    int numChild = 0;
    char destTemp[256];
    signal(SIGINT, sigintHandler);

    printf("\nParent pid: %d\n\n", getpid());
		// ----------- User input and parsing
    printf("How many machines would you like: \n");
    fgets(numChildTemp, sizeof(numChildTemp), stdin);

		printf("At process: %d. What would you like your message to be: \n", getpid());
		fgets(tok.input, sizeof(tok.input), stdin);

		char *pos;
		if ((pos=strchr(tok.input, '\n')) != NULL)
			*pos = '\0';

		printf("What would you like the destination of the message to be: \n");
		fgets(destTemp, sizeof(destTemp), stdin);
		printf("\n\n!!BEGIN!!\n\n");

		tok.dst = atoi(destTemp);
		if(tok.dst == 0){
			exit(0);
		}
		numChild = atoi(numChildTemp);
		if(tok.dst > numChild){
			printf("\tThat machine doesnt exist!!!");
			kill(getpid(), SIGINT);
		}
		// ------------ Pipes
		int pipes[100][2];
		for(int i = 0 ; i < numChild ; i++){
			memcpy(pipes[i], &pipe(fd), sizeof(fd));
		}

		// ------------ Process List
		pidList = (int*) malloc(numChild * sizeof(int));
		pidList[0]=getpid();

		// fork process for n children
		pid = 1;
		for (int i = 1; i <= numChild ; i++) {
			pid = fork();
  		if(pid){
				// parent
				break;
			}
			//child
			pidList[i]= getpid();
			printf("Child (%d): %d Parent: %d List at 0: %d.\n", i, getpid(), getppid(), pidList[0]);
		}
		// communtication process // also in the parent of another process
		// if(getpid() == pidList[0]){
		// 	write(fd[1], &tok, sizeof(token));
		// } else if( getpid() == pidList[tok.dst]) { // we are the destination process
		// 	read(fd[0], &tok, sizeof(token));
		// 	printf("\tReceived string: %s at %d.\n", tok.input, getpid());
		// 	tok.dst = 0;
		// 	strcpy(tok.input, "");
		// 	tok = tok;
		// 	write(fd[1], &tok, sizeof(token));
		// } else if (getpid() == pidList[numChild]){ // tail of the list
		// 	printf("\tAt the tail of the list\n");
		// 	// possibly dup2 the read on this and make it stdin also and ask for another input
		// 	// while also the root parent has a dup2 to standard in that would connect
		// 	// the root parent process to the tail child
		// } else{
		// 	read(fd[0], &tok, sizeof(token));
		// 	printf("\tSeen: %s at %d.\n", tok.input, getpid());
		// 	//write(fd[1], &tok, sizeof(token));
		// }
		wait(NULL);
		printf("Ending: %d\n", getpid());
		sleep(5);

	return(0);
}

void sigintHandler (int sigNum){
  printf("\n!!END sigint with process: %d, who has a parent of: %d!!\n.", getpid(), getppid());
	exit(0);
}
