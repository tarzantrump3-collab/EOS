#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
    pid_t p1, p2;
    int i = 9;
		fork();
    // First fork: creates 2 processes
    p1 = fork();

    // Second fork: both processes from fork 1 call this, creating 4 processes total
    p2 = fork();

    if (p1 < 0 || p2 < 0) {
        perror("fork failure");
        return;
    }

    // Every process will execute this block
    // We check p2 to see if the process is a 'child' of the second fork
    if (p2 == 0) {
        printf("[Child]  PID: %d, PPID: %d, i: %d\n", getpid(), getppid(), ++i);
    } else {
        printf("[Parent] PID: %d, PPID: %d, i: %d\n", getpid(), getppid(), --i);
    }

    // Adding a small sleep or wait ensures the terminal doesn't 
    // mix up the output with the command prompt
    usleep(10000); 
}
