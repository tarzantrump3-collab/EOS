#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p[2];
    int n = 5; 
    pid_t pid;

    if (pipe(p) == -1) {
        perror("pipe");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        pid = fork();

        if (pid == 0) {
            close(p[0]); 
            
            char msg[100];
            sprintf(msg, "Message from Child %d", i);
            
            // Step 1: Send the size of the message
            int len = strlen(msg) + 1;
            write(p[1], &len, sizeof(int));
            
            // Step 2: Send the actual message
            write(p[1], msg, len);
            
            close(p[1]);
            exit(0);
        }
    }

    // Parent Process
    close(p[1]); 

    for (int i = 0; i < n; i++) {
        int msg_len;
        char buffer[100];

        // Read the size first
        if (read(p[0], &msg_len, sizeof(int)) > 0) {
            // Then read exactly that many bytes
            read(p[0], buffer, msg_len);
            printf("Parent received: %s\n", buffer);
        }
    }

    close(p[0]);

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}
