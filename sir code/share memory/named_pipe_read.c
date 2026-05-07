#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define PIPE_PATH "/tmp/my_pipe"

void signal_handler(int sig) {
	printf("signal received type: %d\n", sig);
	signal(sig, SIG_DFL);
	unlink(PIPE_PATH);
	exit(EXIT_SUCCESS);
}

void main()
{
	int ret, pipe = 0;
	char buffer[1024] = {0};
	
	signal(SIGINT, signal_handler);
	signal(SIGPIPE, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);

	ret = mkfifo(PIPE_PATH, S_IRUSR | S_IWUSR);
	if(0 != ret) {
		printf("pipe: %s, create err: %s\n", PIPE_PATH, strerror(errno));
	}

	printf("pipe: %s, create success\n", PIPE_PATH);
	while(1) {
		printf("now opening file...\n");
		pipe = open(PIPE_PATH, O_RDONLY);
		if(pipe < 0) {
			printf("pipe: %s, open err: %d\n", PIPE_PATH, pipe);
			return;
		}
		printf("pipe: %s, openfd: %d\n", PIPE_PATH, pipe);	
		printf("pipe: %s, Reading \n", PIPE_PATH);

		while(1) {	
			ret = read(pipe, buffer, sizeof(buffer));
			if(ret > 0) {
				printf("Read: %d, Buffer: %s\n", ret, buffer);
			} else if(ret == 0) {
				printf("Writer closed the pipe\n");
				break;
			} else {
				printf("error reading: %s", strerror(errno));
				break;
			}
		}
		close(pipe);	
	}
	
	unlink(PIPE_PATH);	
}

