#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("Q3: CPU-bound number printer 10-99 PID=%d\n", getpid());
    fflush(stdout);

    while (1) {
        for (int i = 10; i <= 99; i++) {
            printf("%d ", i);
        }
        printf("\n");
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}
