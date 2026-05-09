#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()

void* slow_worker(void* arg) {
    int duration = *(int*)arg;
    
    printf("Thread (Sleep %ds): Starting...\n", duration);
    sleep(duration); // Simulating a time-consuming task
    printf("Thread (Sleep %ds): Finished.\n", duration);
    
    return NULL;
}

int main() {
    pthread_t threads[3];
    int sleep_times[3] = {3, 1, 2}; // Different durations

    printf("Main: Creating worker threads...\n");

    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, slow_worker, &sleep_times[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    // 1. Main thread reaches this point
    printf("Main: Waiting for threads to join...\n");

    // 2. Joining blocks the main thread
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
        printf("Main: Thread %d has joined.\n", i);
    }

    printf("Main: All threads complete. Exiting program.\n");
    return 0;
}
