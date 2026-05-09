#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4
#define INCREMENTS 100000 // Using a larger number to make the race condition visible

int shared_counter = 0; // Global shared variable

void* increment_counter(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        // Critical Section: Multiple threads are reading/writing here
        shared_counter++; 
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // 1. Create 4 threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // 2. Wait for all to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 3. Display the result
    printf("Expected Value: %d\n", NUM_THREADS * INCREMENTS);
    printf("Actual Value:   %d\n", shared_counter);

    return 0;
}
