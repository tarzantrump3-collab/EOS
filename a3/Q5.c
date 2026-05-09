#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pids[3];

    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pids[i] == 0) {
            int sleep_time = i + 1;
            printf("Child %d started: PID=%d, sleeping %d seconds\n", i + 1, getpid(), sleep_time);
            sleep(sleep_time);
            printf("Child %d exiting after %d seconds\n", i + 1, sleep_time);
            exit(i + 1);
        }
    }

    for (int i = 0; i < 3; i++) {
        int status;
        pid_t done = waitpid(-1, &status, 0);
        if (done < 0) {
            perror("waitpid");
            return EXIT_FAILURE;
        }
        if (WIFEXITED(status)) {
            printf("Parent: child PID=%d exited with status %d\n", done, WEXITSTATUS(status));
        } else {
            printf("Parent: child PID=%d terminated abnormally\n", done);
        }
    }

    return EXIT_SUCCESS;
}
