#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    const char *commands[][3] = {
        {"date", NULL, NULL},
        {"who", NULL, NULL},
        {"pwd", NULL, NULL}
    };

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid == 0) {
            execlp(commands[i][0], commands[i][0], (char *)NULL);
            perror("execlp");
            _exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++) {
        int status;
        pid_t done = waitpid(-1, &status, 0);
        if (done < 0) {
            perror("waitpid");
            return EXIT_FAILURE;
        }
        printf("Parent: child PID=%d finished\n", done);
    }

    return EXIT_SUCCESS;
}
