#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* calculate_square(void* arg) {
    // 1. Cast the void pointer back to an integer pointer
    // 2. Dereference it to get the actual value
    int val = *(int*)arg;
    int square = val * val;
    
    printf("Input: %d -> Square: %d\n", val, square);
    
    pthread_exit(NULL);
}

int main() {
    int num_threads = 4;
    pthread_t threads[num_threads];
    int values[4] = {2, 5, 10, 12};

    for (int i = 0; i < num_threads; i++) {
        // Pass the address of the specific array element
        if (pthread_create(&threads[i], NULL, calculate_square, &values[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
