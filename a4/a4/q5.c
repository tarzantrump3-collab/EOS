#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* calculate_factorial(void* arg) {
    int n = *(int*)arg;
    long long *result = malloc(sizeof(long long)); // Allocate on heap
    *result = 1;

    for (int i = 1; i <= n; i++) {
        *result *= i;
    }

    printf("Thread: Calculated %d! \n", n);
    
    // Return the pointer to the result
    pthread_exit(result); 
}

int main() {
    int num_threads = 3;
    pthread_t threads[num_threads];
    int inputs[3] = {5, 8, 12};
    long long *res_ptr; // To catch the return value

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, calculate_factorial, &inputs[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        // The second argument is a pointer to a pointer (void**)
        // It populates res_ptr with the address passed to pthread_exit
        pthread_join(threads[i], (void**)&res_ptr);
        
        printf("Main: Thread %d returned result: %lld\n", i, *res_ptr);
        
        free(res_ptr); // Clean up the allocated memory
    }

    return 0;
}
