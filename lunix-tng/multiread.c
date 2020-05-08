#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "lunix-chrdev.h"

#define BUFFER_SIZE 20

int main(int argc, char * argv[]) {

	pid_t pid;
	int fd = 0;
	size_t numRead = 0;
	char buf[1];

	if (argc < 3){
     	 	fprintf(stderr,"Usage: ./testMultipleRead infile data_mode[0/1]\n");
      		return 1;
   	}


	if ( (fd = open(argv[1], O_RDONLY)) < 0) {
		perror(argv[1]);
		return 1;
	}

	if ( (pid = fork()) < 0) {
		perror("fork");
		return 1;
	}

	if (pid != 0) {

		printf("parent : ");
		do {
        		numRead = read(fd, buf, 1);
        		if (numRead == -1){
           			perror("read");
           			exit(1);
        		}
        		printf("%c%s", buf[0], (buf[0] == '\n') ? "parent: " : "" );
     		} while(numRead > 0);
		perror("internal error");
		exit(1);
	}

	printf("child: ");
	do {
        	numRead = read(fd, buf, 1);
                if (numRead == -1){
                	perror("read");
                        exit(1);
                }
                printf("%c%s", buf[0], (buf[0] == '\n') ? "child: " : "");
        } while(numRead > 0);

	if (close(fd) < 0) {
		perror("close");
		return 1;
	}

	return 0;
}