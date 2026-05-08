#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int p[2];
    pid_t pid;
    int a = 10, b = 0; 

    pipe(p);
    pid = fork();

    if (pid > 0) {
        close(p[1]);
        int error_code;
        
        if (read(p[0], &error_code, sizeof(int)) > 0) {
            if (error_code == -1) {
                printf("parent: received error from child - division by zero!\n");
            } else {
                printf("parent: result received: %d\n", error_code);
            }
        }
        
        close(p[0]);
    } 
    else {
        close(p[0]);
        int result;

        if (b == 0) {
            int err = -1;
            write(p[1], &err, sizeof(int));
        } else {
            result = a / b;
            write(p[1], &result, sizeof(int));
        }

        close(p[1]);
        exit(0);
    }

    return 0;
}
