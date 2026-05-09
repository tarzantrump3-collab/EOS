#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("Q4: CPU-bound number printer 100-999 PID=%d\n", getpid());
    fflush(stdout);

    while (1) {
        for (int i = 100; i <= 999; i++) {
            printf("%d ", i);
        }
        printf("\n");
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}
