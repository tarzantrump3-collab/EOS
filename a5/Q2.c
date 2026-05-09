#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main(void) {
    pid_t pid = getpid();
    printf("Q2: FIFO scheduling demo PID=%d\n", pid);
    fflush(stdout);

    unsigned long count = 0;
    while (1) {
        printf("Q2: PID=%d count=%lu\n", pid, ++count);
        fflush(stdout);
        usleep(200000);
    }

    return EXIT_SUCCESS;
}
