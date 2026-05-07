#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
       #include <fcntl.h>


#define PIPE_PATH "/tmp/pipe"

int main(){
	int ret, pipe = 0;
	char buffer[100] = {0};
	ret = mkfifo(PIPE_PATH, 0666);
	if( 0 != ret) printf("pipe %s, create err: %s\n", PIPE_PATH, strerror(errno));

	printf("pipe %s, create success: \n", PIPE_PATH);

	while(1){
		printf("now opening file...\n");
		pipe = open(PIPE_PATH, O_RDONLY);
		if(pipe <0){
		       	printf("pipe: %s, open err: %d\n", PIPE_PATH, pipe);
			return 1;	
		}
		printf("pipe: %s, openfd : %d\n", PIPE_PATH, pipe);
		printf("pipe :%s, reading\n", PIPE_PATH);
		printf("now reading\n");
		//while(1){
			ret =	read(pipe, buffer, sizeof(buffer));
	//		printf("read:- %s\n",buffer);
	//
			if(ret > 0) {
			buffer[ret] = '\0';
			printf("Read: %d, Buffer: #%s#\n", ret, buffer);
			} else if(ret == 0) {
				printf("Writer closed the pipe\n");
				break;
			} else {
				printf("error reading: %s", strerror(errno));
				break;
			}
		//	buffer[ret] = '\0';
		//}
		close(pipe);
	memset(buffer,0,sizeof(buffer));
	// buffer[ret+2] = '\0';
	}
	
	close(pipe);
	unlink(PIPE_PATH);




}
