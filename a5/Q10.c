#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void) {
    const int duration = 10;
    time_t start = time(NULL);

    if (start == (time_t)-1) {
        perror("time");
        return EXIT_FAILURE;
    }

    printf("Q10: safe real-time demo PID=%d running for %d seconds\n", getpid(), duration);
    fflush(stdout);

    while (time(NULL) - start < duration) {
        printf("Q10: PID=%d still running, elapsed=%ld\n", getpid(), time(NULL) - start);
        fflush(stdout);
        sleep(1);
    }

    printf("Q10: PID=%d exiting after %d seconds\n", getpid(), duration);
    return EXIT_SUCCESS;
}
