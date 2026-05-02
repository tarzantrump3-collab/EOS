// declare an integer variable. in child change the value of variable and print.//print value of variable without changing it
//

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>

int main()
{
	int x =10;
	pid_t pid = fork();
	fork();
	fork();
	if (pid<0)
	{
		fprintf(stderr,"fork1 failed\n");
		return 1;
	}
	else if(pid ==0)
	{
		x = 20;
	printf("child id %d parent id %d\n",getpid(),getppid());
	printf("child process x =%d\n",x);
	}

	else
	{
		wait(NULL);
	        printf("child id %d parent id %d\n",getpid(),pid);
		printf("parent process %d\n",x);
	}

	return 0;
}
