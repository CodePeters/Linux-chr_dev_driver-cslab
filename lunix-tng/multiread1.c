#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "./lunix-tng-helpcode-20170404/lunix-chrdev.h"

int main(int argc, char * argv[]) {

	int fd = 0;
	size_t numRead = 0;
	char buf[10];

	if (argc < 2){
     	 	fprintf(stderr,"Usage: ./testMultipleRead infile_path\n");
      		return 1;
   	}


	if ( (fd = open(argv[1], O_RDONLY)) < 0) {
		perror(argv[1]);
		return 1;
	}

		do {
        		numRead = read(fd, buf, 10);
        		if (numRead == -1){
           			perror("read");
           			exit(1);
        		}
			printf ("value: %s",buf);
			//printf("ioctl\n");
			ioctl(fd, LUNIX_IOC_TYPE, NULL);
     		} while(numRead > 0);

	if (close(fd) < 0) {
		perror("close");
		return 1;
	}

	return 0;
}
