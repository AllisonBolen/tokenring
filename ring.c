#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

void parse(char* strInput, char** parsedInput);
## test?
int main(int argc, char* argv[])
{
		int status, pid;
		// make fork
    int count = 0;

		pid = fork();
		if(pid < 0){
			// fork failed
			perror("Fork failed\n");
			exit(1);
		}
		else if (!pid){ // child
      printf("child\n");
			exit(0);
		}
		else { // parent
			waitpid(pid, &status, 0);
      printf("parent\n");
		}
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
