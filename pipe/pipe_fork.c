#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    int ret;
    char read_buffer[100];
    pid_t pid;

    ret = pipe(pipefd);
    if (ret != 0) {
        perror("pipe create err");
        return 1;
    }

    printf("pipe created: pipefd[0]: %d, pipefd[1]: %d\n", pipefd[0], pipefd[1]);
    printf("now doing fork to create parent and child\n");

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // --- CHILD PROCESS ---
        // The child wants to READ, so we close the WRITE end
        close(pipefd[1]); 

        printf("Child: waiting to read data from pipe...\n");
        
        // read() is a blocking call; it will wait until the parent writes
        ret = read(pipefd[0], read_buffer, sizeof(read_buffer));
        
        if (ret > 0) {
            read_buffer[ret] = '\0'; // Null-terminate the string
            printf("Child received: %s\n", read_buffer);
        }

        close(pipefd[0]); // Finished reading
        exit(0);

    } else {
        // --- PARENT PROCESS ---
        // The parent wants to WRITE, so we close the READ end
        close(pipefd[0]);

        printf("parent will wait 2 second and send data to pipe\n");
        sleep(2);

        char *buff = "Hi from Parent";
        ret = write(pipefd[1], (const void *)buff, strlen(buff));
        printf("parent write: %d bytes in pipe to child\n", ret);

        close(pipefd[1]); // Finished writing
    }

    return 0;
}
