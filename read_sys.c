#include<stdio.h>
#include<unistd.h>
#include <errno.h>
#include<string.h>


#define STDIN_FD 0
#define STDOUT_FD 1
#define STDERR_FD 2

void main()
{
	int ret;
	char rd_buf[128] = {0};

	//part 1 reading keyboard

	ret = read(STDIN_FD, (void*)rd_buf,sizeof(rd_buf)-1);

	if(ret ==-1){
		printf("read error: %d",errno);
		return;
	}
		
	printf("read return: %d bytes\n",ret);

	printf("rd_buff: %s\n",rd_buf);
		
	
	// part 2 writing
		//
	char *str = "chetan";
	ret = write(STDOUT_FD, (const void*)str, strlen(str));
	if(ret ==-1){
		printf("write error : %d\n",errno);
		return;
	}
	printf("\nwrite: %d bytes\n",ret);

	//part 3 
		
	ret = read(6,(void*) rd_buf,sizeof(rd_buf)-1);
	if(ret ==-1){
                printf("read error : %d, %s\n",errno,strerror(errno));
		perror("PERROR: READ");
                return;
        }

	return;
} 
