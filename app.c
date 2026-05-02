#include<stdio.h>
#include<unistd.h>

void main(int argc, char *argv[])
{
	printf("this is app of app.c\n");
	printf("argument recieved :%d\n", argc);
	for (int i =0; i<argc; ++i)
	{
		printf("\narg: %d,  %s \n", i, argv[i]);
	}
}

