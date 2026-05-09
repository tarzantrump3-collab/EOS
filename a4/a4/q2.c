#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 

#define NUM_THREADS 5

void* print_thread_info(void* arg) {
    // Cast the argument back to an integer
    int thread_num = *(int*)arg;
    
    // getpid() returns the Process ID, which remains the same for all threads
    printf("Thread #%d: Working in Process ID %d\n", thread_num, getpid());
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // 1. Creation Loop
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i; // Store ID in an array to avoid race conditions
        if (pthread_create(&threads[i], NULL, print_thread_info, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    // 2. Joining Loop
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished execution.\n");
    return 0;
}
