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

	pid = fork();
	if(pid > 0) {
		//parent 
		close(pipefd[0]); //close read end, parent needs only to write
		
		int cnt = 0;
		do {
			char buff[256]= {0};
			int rd = read(0, (void *) buff, sizeof(buff) / sizeof(buff[0]));
			printf("read from STDIN: %d bytes\n", rd);
			
			if(rd > 0) {
				cnt++;
				ret = write(pipefd[1], (const void *)buff, rd);
				printf("parent write: %d bytes in pipe to child\n", ret);
			}
			
			if(cnt >= 10) {
				printf("10 inputs taken from user, now terminate all\n");
				break;
			}

		} while(1);

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
		
		do {
			char buff[256] = {0};
			printf("child waiting for data from pipe\n");
			
			ret = read(pipefd[0], (void *) buff, sizeof(buff) / sizeof(buff[0]));
			if(ret <= 0) {
				printf("pipe closed / err exit: ret:%d,errno:%d,errno str:%s\n", ret, errno, strerror(errno));
				break;
			} 	

			printf("child read: %d bytes in pipe from parent\n", ret);
			printf("child read: %s\n", buff);
		
		} while(1);
		
		close(pipefd[0]); //close read end, no use of read now
		exit(EXIT_SUCCESS);
	} else {
		perror("fork err");
		return;
	}
}
