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
    char* output = "STRING OUTPUT";
    printf("Parent pid: %d\n\n", getpid());

    pid = fork();
    if(pid < 0) {
        printf("Error");
        exit(1);
    } else if (pid == 0) { // child
        printf("Child (%d): %d Parent: %d\n", 1, getpid(), getppid());

        pipe(fd);
        close(fd[1]);
        printf("Reading from pipe??\n");
        read(fd[0], buffer, sizeof(buffer));
        printf("Received string: %s at %d\n", buffer, getpid());

        bpid = fork();
        if(bpid < 0) {
            printf("Error");
            exit(1);
        } else if (bpid == 0) { // child
            printf("Child (%d): %d Parent: %d\n", 2, getpid(), getppid());

            pipe(fd);
            close(fd[1]);
            printf("Reading from pipe??\n");
            read(fd[0], buffer, sizeof(buffer));
            printf("Received string: %s at %d\n", buffer, getpid());
            cpid = fork();
            if(cpid < 0) {
                printf("Error");
                exit(1);
            } else if (cpid == 0) { // child
                printf("Child (%d): %d Parent: %d\n", 3, getpid(), getppid());
                close(fd[1]);
                printf("Reading from pipe??\n");
                read(fd[0], buffer, sizeof(buffer));
                printf("Received string: %s at %d\n", buffer, getpid());
                exit(0);
            } else  {
              close(fd[0]);
              printf("writing to pipe??\n");
              write(fd[1], output, (strlen(output)+1));
              wait(NULL);
            }

            exit(0);
        } else  {
          close(fd[0]);
          printf("writing to pipe??\n");
          write(fd[1], output, (strlen(output)+1));
          wait(NULL);
        }

        exit(0);
    } else  {
      close(fd[0]);
      printf("writing to pipe??\n");
      write(fd[1], output, (strlen(output)+1));
      wait(NULL);
    }
	return(0);
}

void parse(char * strInput, char** parsedInput)
{
	printf("execution\n");
}
