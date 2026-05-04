#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0) {
	    // this is child process section
        sleep(1);

/*	for(int i =0;i<15;i++){

	printf("child pid: %d\n", getpid());
        printf("child ppid: %d\n", getppid());
	}
*/
        printf("child pid: %d\n", getpid());
        printf("child ppid: %d\n", getppid());
	printf("exit child\n");

        exit(EXIT_SUCCESS);
    } else if (pid == -1) {
	    // forked failed
        perror("fork err\n");
    } else {
        int stat_loc;
	// this is parent process section
	//
        printf("parent pid: %d\n", getpid());
        printf("parent ppid: %d\n", getppid());
        wait(&stat_loc);
        printf("child exit stat: %d\n", stat_loc);
        exit(EXIT_SUCCESS);
    }
}
