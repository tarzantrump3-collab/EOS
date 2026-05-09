#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        printf("Child: exiting immediately (PID=%d)\n", getpid());
        return EXIT_SUCCESS;
    }

    printf("Parent: child created as PID=%d. Sleeping for 5 seconds before wait()...\n", pid);
    printf("Use 'ps -l' in another terminal during the sleep to observe the zombie process.\n");
    sleep(5);

    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    printf("Parent: reaped child PID=%d\n", pid);
    return EXIT_SUCCESS;
}
