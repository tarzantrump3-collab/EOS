#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
	int pipefd[2];
	int ret;
	char read_buffer[100];
	pid_t pid;

	ret = pipe(pipefd);
	if (ret != 0){
		perror("pipe create error");
		return ;
	}
	sleep(1);
	printf("\t\tpipe create pipefd[0]: %d, pipefd[1]: %d\n", pipefd[0], pipefd[1]);
	sleep(1);
	printf("\nnow doing fork create parent and child\n");
	sleep(1);

	pid = fork();

	if(pid >0){
		/// parent
		//
		close(pipefd[0]); // close read end of parent no need in this process
		printf("\nparent will wait 2 second and send data to pipe\n");
       		 sleep(2);
		
		 char *buff = "hi this text send by parent";

		 ret = write(pipefd[1], (const void *)buff,strlen(buff));

		printf("\nparent write: %d bytes in pipe to child\n", ret);

       		close(pipefd[1]); // Finished writing

		printf("\nparent now waiting for child to terminate\n");
		wait(NULL);

		printf("\nparent recived from child terminate parent\n");

		return ;
	}
	else if (pid == 0){
		close(pipefd[1]); // close read end of child no need in this process
		char buff[256] = {0};
		printf("\nchild waiting for data\n");
		
		ret = read(pipefd[0], (void *)buff, sizeof(buff));

		printf("\nchild read byte = %d\n", ret);
		printf("child read data :- %s\n",buff);

		close(pipefd[0]); // finish task child

		printf("\nchild terminate\n");

		return;


	}else {
		perror("fork err");
		return;
	}


}
