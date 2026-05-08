#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p1[2]; 
    int p2[2];
    pid_t pid1, pid2;

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        return 1;
    }

    pid1 = fork();

    if (pid1 == 0) {
        int num = 5;
        close(p1[0]);
        close(p2[0]);
        close(p2[1]);
        write(p1[1], &num, sizeof(int));
        close(p1[1]);
        exit(0);
    }

    pid2 = fork();

    if (pid2 == 0) {
        int val;
        close(p1[1]);
        close(p2[0]);
        read(p1[0], &val, sizeof(int));
        val = val * val;
        write(p2[1], &val, sizeof(int));
        close(p1[0]);
        close(p2[1]);
        exit(0);
    }

    //logic in the parent
    int final_val;
    close(p1[0]);
    close(p1[1]);
    close(p2[1]);
    
    read(p2[0], &final_val, sizeof(int));
    final_val = final_val + 10;
    
    printf("Final Result: %d\n", final_val);
    
    close(p2[0]);
    wait(NULL);
    wait(NULL);

    return 0;
}
