#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("mini-shell> ");
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1) {
            break;
        }

        if (line[0] == '\n') {
            continue;
        }

        // Reap any finished background children
        int bg_status;
        while (waitpid(-1, &bg_status, WNOHANG) > 0) {
            ;
        }

        // Trim newline
        line[strcspn(line, "\n")] = '\0';

        char *token;
        char *args[128];
        int argc = 0;
        int background = 0;

        token = strtok(line, " \t");
        while (token != NULL && argc < (int)(sizeof(args) / sizeof(args[0])) - 1) {
            args[argc++] = token;
            token = strtok(NULL, " \t");
        }
        args[argc] = NULL;

        if (argc == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (argc < 2) {
                fprintf(stderr, "cd: missing operand\n");
            } else if (chdir(args[1]) != 0) {
                perror("cd");
            }
            continue;
        }

        if (argc > 0 && strcmp(args[argc - 1], "&") == 0) {
            background = 1;
            args[argc - 1] = NULL;
            argc--;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            _exit(EXIT_FAILURE);
        }

        if (!background) {
            int status;
            if (waitpid(pid, &status, 0) < 0) {
                perror("waitpid");
            }
        } else {
            printf("Started background process PID=%d\n", pid);
        }
    }

    free(line);
    return EXIT_SUCCESS;
}
