#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// This is the function the thread will execute
void* thread_function(void* arg) {
    printf("Hello from thread\n");
    return NULL;
}

int main() {
    pthread_t my_thread; // Thread identifier

    // 1. Create the thread
    // Arguments: (thread id, attributes, function to run, arguments to function)
    if (pthread_create(&my_thread, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // 2. Print from the main thread
    printf("Hello from main\n");

    // 3. Wait for the thread to finish
    // Without this, main might exit before the thread prints
    pthread_join(my_thread, NULL);

    return 0;
}
