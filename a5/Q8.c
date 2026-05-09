#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    const int n = 1000;
    const int iterations = 20000;
    double values[n];
    for (int i = 0; i < n; i++) {
        values[i] = 1.0001 + 0.00001 * i;
    }

    struct timespec start, end;
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) {
        perror("clock_gettime");
        return EXIT_FAILURE;
    }

    double result = 1.0;
    for (int iter = 0; iter < iterations; iter++) {
        double product = 1.0;
        for (int i = 0; i < n; i++) {
            product *= values[i];
        }
        result += product;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0) {
        perror("clock_gettime");
        return EXIT_FAILURE;
    }

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Q8: computation finished in %.6f seconds, result=%f\n", elapsed, result);
    return EXIT_SUCCESS;
}
