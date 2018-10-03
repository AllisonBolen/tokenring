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

    printf("\nRoot Parent pid: %d\n\n", getpid());
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


		numChild = atoi(numChildTemp);
		if(tok.dst > numChild){
			printf("\tThat machine doesnt exist!!!");
			kill(getpid(), SIGINT);
		}
		// ------------ Pipes
		int pipes[60][2];
		for(int i = 0 ; i < numChild ; i++){
			memcpy(pipes[i], &fd, sizeof(fd));
		}

		// ------------ Process List
		pidList = (int*) malloc(numChild * sizeof(int));
		pidList[0]=getpid();

		// fork process for n children
		pid = 1;
		for (int i = 0; i < numChild-1 ; i++) {
			pid = fork();
  		if(pid){
				// parent
				break;
			}
			//child
			pidList[i+1]= getpid();
			printf("Child (%d): %d Parent: %d.\n", i, getpid(), getppid());
		}
		wait(NULL);
		// for(int j = 0; j < numChild; j++) {
    //     printf("%d ", pidList[j]);
    // }
		// printf("\n");

		// communtication process all processes have this code
		while(1){
			if(getpid() == pidList[0]){ // root parent
				// ?? read(pipes[numChild][READ], &tok, sizeof(token) ); // read from tail pipe
				tok.dst = atoi(destTemp);
				if(tok.dst == 0){
					exit(0);
				}
				// write our message
				if(tok.dst == 0){
					read(pipes[numChild-1][READ], &tok, sizeof(token));
				}
				write(pipes[0][WRITE], &tok, sizeof(token)); // write to next pipe
			}
			if( getpid() == pidList[tok.dst]) { // we are the destination process
				read(pipes[tok.dst-1][READ], &tok, sizeof(token)); // read from previous pipe
				printf("\tDESTINATION Received string: %s at %d.\n", tok.input, getpid());
				tok.dst = 0;
				strcpy(tok.input, "");
				tok = tok;
				write(pipes[tok.dst][WRITE], &tok, sizeof(token)); // write to next pipe
			} else if (getpid() == pidList[numChild-1]){ // tail of the list
				printf("\tAt the tail of the list\n");
				// possibly dup2 the read on this and make it stdin also and ask for another input
				// while also the root parent has a dup2 to standard in that would connect
				// the root parent process to the tail child
				read(pipes[numChild-2][READ], &tok, sizeof(token)); // read of the previous pipe
				write(pipes[numChild-1][WRITE], &tok, sizeof(token)); // write to the next one
			} else{
				//read(pipes[?][READ], &tok, sizeof(token));
				printf("\tSeen: %s at %d.\n", tok.input, getpid());
				//write(pipes[?][WRITE], &tok, sizeof(token));
				return 0;
			}
			//// gotta line up my lists
			//while(1){
			sleep(5);
		}
	return(0);
}

void sigintHandler (int sigNum){
  printf("\n!!END sigint with process: %d, who has a parent of: %d!!\n.", getpid(), getppid());
	free(pidList);
	exit(0);
}
