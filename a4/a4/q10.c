#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 3
#define MAX_TASKS 10

typedef struct {
    int task_id;
    int data;
} Task;

Task task_queue[MAX_TASKS];
int task_count = 0;

pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;

void execute_task(Task* task, int worker_id) {
    int result = task->data * task->data; // Simple computation (square)
    printf("Worker %d: Task %d completed (Square of %d is %d)\n", 
            worker_id, task->task_id, task->data, result);
}

void* worker_routine(void* arg) {
    int id = *(int*)arg;
    while (1) {
        Task task;

        pthread_mutex_lock(&queue_mutex);
        // Wait until there is work in the queue
        while (task_count == 0) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        // Grab the next task
        task = task_queue[--task_count];
        pthread_mutex_unlock(&queue_mutex);

        execute_task(&task, id);
        usleep(500000); // Simulate work time
    }
    return NULL;
}

int main() {
    pthread_t workers[THREAD_POOL_SIZE];
    int worker_ids[THREAD_POOL_SIZE];

    pthread_mutex_init(&queue_mutex, NULL);
    pthread_cond_init(&queue_cond, NULL);

    // 1. Start Worker Threads
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        worker_ids[i] = i;
        pthread_create(&workers[i], NULL, worker_routine, &worker_ids[i]);
    }

    // 2. Dynamically add tasks to the queue
    for (int i = 0; i < MAX_TASKS; i++) {
        pthread_mutex_lock(&queue_mutex);
        task_queue[task_count].task_id = i;
        task_queue[task_count].data = i + 1;
        task_count++;
        printf("Main: Added Task %d to queue\n", i);
        pthread_cond_signal(&queue_cond); // Wake up one worker
        pthread_mutex_unlock(&queue_mutex);
        usleep(100000); // Space out task arrival
    }

    // Give workers time to finish before exiting
    sleep(5);
    return 0;
}
