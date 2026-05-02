#include <stdio.h>
#include <unistd.h>

void main()
{
    pid_t pid;

    pid = fork();
    if(pid == 0) {
        //child
        printf("child pid: %d, ppid: %d\n", getpid(), getppid());
        //fork();
    } else if (pid > 0) {
        //parent
        printf("parent pid: %d, ppid: %d\n", getpid(), getppid());
        //fork();
    } else {
        perror("fork failure");
    }
}
