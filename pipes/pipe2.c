#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main() {
    int pipefd[2];
    char buffer[100];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
sleep(1);
printf("Pipe created with file descriptors: %d (read end), %d (write end)\n", pipefd[0], pipefd[1]);
sleep(1);

pid_t pid = fork();
if(pid == 0)
{
    close(pipefd[0]); // Close the read end in the child process
    const char *message = "Hello from the child process!";
    int ret = write(pipefd[1], message, strlen(message) + 1);
    close(pipefd[1]); // Close the write end after writing
    if (ret == -1) {
        perror("write");
        return 1;
    }

}
//ose the pipe file descriptors
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}