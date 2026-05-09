#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* infinite_loop_worker(void* arg) {
    printf("Thread: Starting infinite loop...\n");
    
    while (1) {
        printf("Thread: Still running...\n");
        sleep(1); // This is a cancellation point
    }
    
    return NULL; // This line will never be reached
}

int main() {
    pthread_t my_thread;

    // 1. Start the infinite thread
    if (pthread_create(&my_thread, NULL, infinite_loop_worker, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // 2. Let it run for a few seconds
    sleep(3);

    // 3. Cancel the thread
    printf("Main: Sending cancellation request...\n");
    pthread_cancel(my_thread);

    // 4. Always join even after canceling to clean up resources
    void* res;
    pthread_join(my_thread, &res);

    if (res == PTHREAD_CANCELED) {
        printf("Main: Thread was successfully canceled.\n");
    } else {
        printf("Main: Thread completed normally (unexpected).\n");
    }

    return 0;
}
