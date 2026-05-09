#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS_TO_PRODUCE 10

int buffer[BUFFER_SIZE];
int count = 0; // Current number of items in buffer

pthread_mutex_t mutex;
pthread_cond_t cond_full;  // Signaled when buffer has space
pthread_cond_t cond_empty; // Signaled when buffer has data

void* producer(void* arg) {
    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        pthread_mutex_lock(&mutex);

        // 1. Wait if buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_full, &mutex);
        }

        // 2. Add item
        buffer[count] = i;
        printf("Producer: Inserted %d at index %d\n", i, count);
        count++;

        // 3. Signal consumer that data is available
        pthread_cond_signal(&cond_empty);
        pthread_mutex_unlock(&mutex);
        
        usleep(100000); // Small delay for visibility
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        pthread_mutex_lock(&mutex);

        // 1. Wait if buffer is empty
        while (count == 0) {
            pthread_cond_wait(&cond_empty, &mutex);
        }

        // 2. Remove item
        count--;
        int item = buffer[count];
        printf("Consumer: Removed %d from index %d\n", item, count);

        // 3. Signal producer that space is available
        pthread_cond_signal(&cond_full);
        pthread_mutex_unlock(&mutex);

        usleep(150000); // Consumer is slightly slower
    }
    return NULL;
}

int main() {
    pthread_t prod_tid, cons_tid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_full, NULL);
    pthread_cond_init(&cond_empty, NULL);

    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_full);
    pthread_cond_destroy(&cond_empty);

    return 0;
}
