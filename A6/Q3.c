#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n = 4; 
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int size = 12;
    int part = size / n;
    int fd[n][2];
    pid_t pid;

    for (int i = 0; i < n; i++) {
        pipe(fd[i]);
        pid = fork();

        if (pid == 0) {
            int start = i * part;
            int end = (i == n - 1) ? size : (i + 1) * part;
            int sum = 0;

            close(fd[i][0]);
            for (int j = start; j < end; j++) {
                sum += arr[j];
            }
            write(fd[i][1], &sum, sizeof(int));
            close(fd[i][1]);
            exit(0);
        } else {
            close(fd[i][1]);
        }
    }

    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        int child_sum;
        read(fd[i][0], &child_sum, sizeof(int));
        total_sum += child_sum;
        close(fd[i][0]);
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Total Sum: %d\n", total_sum);

    return 0;
}
