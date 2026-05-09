#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4
#define INCREMENTS 100000

int shared_counter = 0;
// 1. Declare the Mutex
pthread_mutex_t counter_mutex;

void* increment_counter(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        // 2. Lock the mutex before entering the Critical Section
        pthread_mutex_lock(&counter_mutex);
        
        shared_counter++; // Safe now!
        
        // 3. Unlock the mutex after leaving the Critical Section
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // 4. Initialize the mutex
    pthread_mutex_init(&counter_mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 5. Clean up the mutex
    pthread_mutex_destroy(&counter_mutex);

    printf("Expected Value: %d\n", NUM_THREADS * INCREMENTS);
    printf("Actual Value:   %d\n", shared_counter);

    return 0;
}
