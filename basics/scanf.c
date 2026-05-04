#include <stdio.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
#define STDIN_FD 0
#define STDOUT_FD 1
#define STDERR_FD 2 


void main() {

	 num = read(STDIN_FD, (void *)rd_buf, sizeof(rd_buf)-1);
        if (num ==-1) {

		printf("\nRead error: %d, %s", errno, strerror(errno));
                perror("PERROR: READ");

		return;
        }
        printf("read returned : %d bytes\n", num);

	printf("\nwrite : %d bytes\n",num);
        
      
     
    
    
   
}

