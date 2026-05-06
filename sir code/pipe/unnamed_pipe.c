#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void main() {
	int pipefd[2], ret;
	pid_t pid;
	
	ret = pipe(pipefd);
	if(ret != 0) {
		perror("pipe create err");
		return;
	}

	sleep(1);
	printf("pipe created: pipedfd[0]:%d, pipefd[1]: %d\n", pipefd[0], pipefd[1]);
	sleep(1);

	printf("now doing fork to create parent and child\n");
	sleep(1);

	pid = fork();
	if(pid > 0) {
		//parent 
		close(pipefd[0]); //close read end, parent needs only to write
		
		printf("parent will wait 2 second and send data to pipe\n");
		sleep(2);
		
		char *buff = "Hi from Parent";
		ret = write(pipefd[1], (const void *)buff, strlen(buff));
		printf("parent write: %d bytes in pipe to child\n", ret);

		close(pipefd[1]); //close write end, no use of write now
		printf("parent now waiting for child to terminate\n");
		
		wait(NULL);
		printf("parent received child termination, now parent terminating\n");
		/*wait for child to exit, 
		 * so no zombie if child terminated earlier
		 * or no orphan if parent terminated earlier
		 */
		
		return;
	} else if (pid == 0) {
		//child
		close(pipefd[1]); //close write end, child only needs to read
		
		char buff[256] = {0};
		printf("child waiting for data from pipe\n");
		
		ret = read(pipefd[0], (void *) buff, sizeof(buff) / sizeof(buff[0]));
		
		printf("child read: %d bytes in pipe from parent\n", ret);
		printf("child read: %s\n", buff);

		close(pipefd[0]); //close read end, no use of read now
		exit(EXIT_SUCCESS);
	} else {
		perror("fork err");
		return;
	}
}
