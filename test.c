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
int pipes[60][2];
int numChild = 0;

typedef struct {
  char input[256];
  int dst;
} token;
typedef struct{
	int FD_READ;
	int FD_WRITE;
} myPipeDscp;
void sigintHandler (int sigNum);

#define WRITE 1
#define READ 0

int main(int argc, char* argv[])
{
		int pid;
    // char buffer[256];
		token tok;
    char numChildTemp[256];
    char destTemp[256];
    signal(SIGINT, sigintHandler);

    printf("\nRoot Parent pid: %d\n\n", getpid());
		// ----------- User input and parsing
    printf("How many machines would you like: \n");
    fgets(numChildTemp, sizeof(numChildTemp), stdin);
		numChild = atoi(numChildTemp);


		// ------------ Pipes
		int pipes[60][2];
		for(int i = 0 ; i < numChild ; i++){
			pipe(pipes[i]);
		}

		// ------------ Process List
		pidList = (int*) malloc(numChild * sizeof(int));
		pidList[0]=getpid();

		// fork process for n children
		myPipeDscp myPipes;
		myPipes.FD_WRITE = pipes[0][WRITE];
		myPipes.FD_READ = pipes[numChild-1][READ];
		printf("Child (%d): %d Parent: %d READ: %d WRITE: %d.\n", 0, getpid(), getppid(), myPipes.FD_READ, myPipes.FD_WRITE);
		for (int i = 1; i < numChild ; i++) {
  		if((pid = fork())){// parent
				;
			}else {
			//child
			myPipes.FD_WRITE = pipes[i][WRITE];
			myPipes.FD_READ = pipes[i-1][READ];
			pidList[i]= getpid();
			printf("Child (%d): %d Parent: %d READ: %d WRITE: %d.\n", i, getpid(), getppid(), myPipes.FD_READ, myPipes.FD_WRITE);
			break;
			}
		}
		wait(NULL);

		// communtication process all processes have this code

		//while(1){
			if(pid == 1){ // root parent
				printf("What would you like your message to be: \n", getpid());
				fgets(tok.input, sizeof(tok.input), stdin);
				char *pos;
				if ((pos=strchr(tok.input, '\n')) != NULL)
					*pos = '\0';
				printf("What would you like the destination of the message to be: \n");
				fgets(destTemp, sizeof(destTemp), stdin);
				tok.dst = atoi(destTemp);
				if(tok.dst > numChild){
					printf("\tThat machine doesnt exist!!!");
					kill(getpid(), SIGINT);
				}
				write(myPipes.FD_WRITE, &tok, sizeof(token)); // write to next pipe
			}else{ // children
				printf("Child: %d Parent: %d READ: %d WRITE: %d Token DST: %d Token Message: '%s'.\n", getpid(), getppid(), myPipes.FD_READ, myPipes.FD_WRITE, tok.dst, tok.input);
				read(myPipes.FD_READ, &tok, sizeof(token));
				if( getpid() == tok.dst) { // we are the destination process
					printf("\tDESTINATION Received string: %s at %d.\n", tok.input, getpid());
					tok.dst = 0;
					strcpy(tok.input, "");
					tok = tok;
					write(myPipes.FD_WRITE, &tok, sizeof(token)); // write to next pipe
				}
			}
			sleep(5);
	return(0);
}

void sigintHandler (int sigNum){
	for(int i = 0 ; i < numChild; i++){
		close(pipes[i][WRITE]);
		close(pipes[i][READ]);
	}
  printf("\n!!END sigint with process: %d, who has a parent of: %d!!\n.", getpid(), getppid());
	free(pidList);
	exit(0);
}
