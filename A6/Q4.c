#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int p[2];
    pid_t pid;
    char signal = 'G';

    pipe(p);
    pid = fork();

    if (pid > 0) {
        close(p[0]);
        
        printf("Parent: Printing first...\n");
        sleep(1); 
        
        write(p[1], &signal, 1);
        close(p[1]);
    } 
    else {
        close(p[1]);
        
        read(p[0], &signal, 1);
        
        printf("Child: Parent finished, now I am printing.\n");
        
        close(p[0]);
        exit(0);
    }

    return 0;
}
