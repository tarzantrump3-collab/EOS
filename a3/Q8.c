#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        sleep(3);
        printf("Orphan child: PID=%d, PPID=%d\n", getpid(), getppid());
        return EXIT_SUCCESS;
    }

    printf("Parent: PID=%d, exiting before child. Child PID=%d\n", getpid(), pid);
    return EXIT_SUCCESS;
}
