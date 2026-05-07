#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define PIPE_PATH "/tmp/my_pipe"


void signal_handler(int sig)
{
	printf("signal received : %d\n", sig);
}

void main()
{
	int ret, pipe = 0;
	
	signal(SIGPIPE, signal_handler);

	pipe = open(PIPE_PATH, O_WRONLY);
	if(pipe < 0) {
		printf("pipe: %s, open err: %s\n", PIPE_PATH, strerror(errno));
		return;
	}
	printf("pipe: %s, openfd: %d\n", PIPE_PATH, pipe);	
	printf("pipe: %s, Writing \n", PIPE_PATH);
	int count = 0;
	while(1) {
		char buffer[1024] = {0};

		printf("reading from STDIN\n");
		int rd = read(0, buffer, sizeof(buffer));
		if(rd <= 0) {
			printf("read from stdin error: %s\n", strerror(errno));
			break;
		}
		
		int wr = write(pipe, buffer, rd);
		if(wr > 0) {
			printf("Write: %d, Buffer: %s\n", wr, buffer);
		}else {
			printf("Write: %d bytes: %s\n", wr, strerror(errno));
			break;
		}

	}
	close(pipe);
}

