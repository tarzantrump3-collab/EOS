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

        char buffer[100];
        ret = mkfifo(PIPE_PATH, 0666);
        if( 0 != ret) printf("pipe %s, create err: %s\n", PIPE_PATH, strerror(errno));

        printf("pipe %s, create success: \n", PIPE_PATH);

        while(1){
                printf("now opening file...\n");
                pipe = open(PIPE_PATH, O_WRONLY);
                if(pipe <0){
                        printf("pipe: %s, open err: %d\n", PIPE_PATH, pipe);
                        return 1;
                }
                printf("pipe: %s, openfd : %d\n", PIPE_PATH, pipe);
                printf("pipe :%s, now write\n", PIPE_PATH);
               // printf("now write\t\t");

              
                      ret =  read(0, buffer, sizeof(buffer));
                        //printf(":- %s\n",buffer);
			write(pipe, buffer, ret);
                
        }





}

