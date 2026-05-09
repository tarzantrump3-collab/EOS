#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t child1 = fork();
    if (child1 < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child1 == 0) {
        // Child 1 creates a grandchild
        pid_t grandchild = fork();
        if (grandchild < 0) {
            perror("fork");
            _exit(EXIT_FAILURE);
        }
        if (grandchild == 0) {
            printf("Grandchild: PID=%d, PPID=%d\n", getpid(), getppid());
            _exit(EXIT_SUCCESS);
        }
        printf("Child1: PID=%d, PPID=%d, created Grandchild PID=%d\n", getpid(), getppid(), grandchild);
        waitpid(grandchild, NULL, 0);
        _exit(EXIT_SUCCESS);
    }

    // Parent creates Child 2
    pid_t child2 = fork();
    if (child2 < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child2 == 0) {
        printf("Child2: PID=%d, PPID=%d\n", getpid(), getppid());
        return EXIT_SUCCESS;
    }

    printf("Parent: PID=%d, created Child1 PID=%d and Child2 PID=%d\n", getpid(), child1, child2);
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return EXIT_SUCCESS;
}
