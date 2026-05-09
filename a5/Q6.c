#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("Q6: starvation demo PID=%d\n", getpid());
    fflush(stdout);

    unsigned long count = 0;
    while (1) {
        count++;
        if ((count & 0xFFFFFF) == 0) {
            printf("Q6: PID=%d count=%lu\n", getpid(), count);
            fflush(stdout);
        }
    }

    return EXIT_SUCCESS;
}
