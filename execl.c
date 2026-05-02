:#include<stdio.h>
#include<unistd.h>
#include<errno.h>

void main()
{
	int ret;

	printf("this is process of excel.c\n");
	fflush(stdout);

	ret = execl("app.out", "HELLO", "1", "2", (char *)NULL);
	if(ret  == -1) perror("execl failed");

	printf("if succesfull this line never prints\n");
}
