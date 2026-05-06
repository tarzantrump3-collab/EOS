#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
   
    char buffer[100];
    int fd1[2], fd2[2];
    const char str[] = "Hello, World!";
    pid_t pid;
    // Create a pipe
    if (pipe(fd1) == -1) {
        perror("pipe");
        return 1;
    }

    if (pipe(fd2) == -1) {
        perror("pipe");
        return 1; 
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }   
    if (pid == 0) { // Child process
        close(fd1[1]); // Close the write end of the first pipe
        close(fd2[0]); // Close the read end of the second pipe

        // Read from the first pipe
        read(fd1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        write(fd2[1], str, strlen(str) + 1);

        close(fd1[0]);
        close(fd2[1]);
    } else { // Parent process
        close(fd1[0]); // Close the read end of the first pipe
        close(fd2[1]); // Close the write end of the second pipe

        // Write to the first pipe
        write(fd1[1], str, strlen(str) + 1);

        // Read from the second pipe
        read(fd2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);

        // Close the remaining file descriptors
        close(fd1[1]);
        close(fd2[0]);
    }
    // Close the pipe file descriptors
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);

    return 0;
}