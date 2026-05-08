#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

int main() {
    int p1[2]; 
    int p2[2]; 
    pid_t pid;
    char buffer[100];
    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { 

        char *message = "hello from parent";
        
        close(p1[0]); // pipe 1
        close(p2[1]); // pipe 2

        printf("Parent: Sending message... '%s'\n", message);
        write(p1[1], message, strlen(message) + 1);


        read(p2[0], buffer, sizeof(buffer));
        printf("Parent: Received back... '%s'\n", buffer);

        close(p1[1]);
        close(p2[0]);
    } 
    else { 

        close(p1[1]); //pipe 1
        close(p2[0]); // pipe 2


        read(p1[0], buffer, sizeof(buffer));
        
        for (int i = 0; buffer[i] != '\0'; i++) {
            buffer[i] = toupper(buffer[i]);
        }

        write(p2[1], buffer, strlen(buffer) + 1);

        close(p1[0]);
        close(p2[1]);
        exit(0);
    }

    return 0;
}
