#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create the pipe
    // pipefd[0] is the read end, pipefd[1] is the write end
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // --- First Child Process: 'ls' ---
    pid1 = fork();
    if (pid1 == 0) {
        // Redirect stdout to the pipe's write end
        dup2(pipefd[1], STDOUT_FILENO);

        // Close unused pipe ends
        close(pipefd[0]);
        close(pipefd[1]);

        // Execute ls
        char *args[] = {"ls", "-la", NULL};
        execvp(args[0], args);
        
        perror("execvp ls");
        exit(EXIT_FAILURE);
    }

    // --- Second Child Process: 'grep txt' ---
    pid2 = fork();
    if (pid2 == 0) {
        // Redirect stdin to the pipe's read end
        dup2(pipefd[0], STDIN_FILENO);

        // Close unused pipe ends
        close(pipefd[0]);
        close(pipefd[1]);

        // Execute grep
        char *args[] = {"grep", "txt", NULL};
        execvp(args[0], args);

        perror("execvp grep");
        exit(EXIT_FAILURE);
    }

    // --- Parent Process ---
    // Parent must close its copies of the pipe descriptors
    // otherwise the second child will wait forever for input to end
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
