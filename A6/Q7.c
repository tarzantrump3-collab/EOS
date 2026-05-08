#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p[2];
    pid_t pid1, pid2;

    if (pipe(p) == -1) {
        return 1;
    }

    pid1 = fork();
    if (pid1 == 0) {
        dup2(p[1], STDOUT_FILENO);
        close(p[0]);
        close(p[1]);
        char *args[] = {"ls", NULL};
        execvp(args[0], args);
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        dup2(p[0], STDIN_FILENO);
        close(p[0]);
        close(p[1]);
        char *args[] = {"grep", "txt", NULL};
        execvp(args[0], args);
        exit(1);
    }

    close(p[0]);
    close(p[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
