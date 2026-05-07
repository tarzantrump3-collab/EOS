#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shmptr;
    /*Create shared memory*/
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if(shmid < 0) {
        perror("shmget");
        return -1;
    }

    printf("Shared Memory ID : %d\n", shmid);

    /* Attach shared memory into process virtual address space*/
    shmptr = shmat(shmid, NULL, 0);
    if(shmptr == (void *) -1) {
        perror("shmat");
        return -1;
    }

    printf("Shared memory attached at : %p\n", shmptr);

    /*Write directly into shared memory*/
    strcpy(shmptr, "HELLO FROM WRITER");
    printf("Data written : %s\n", shmptr);
    printf("Sleeping 30 sec...\n");
    sleep(30);

    /*Detach memory from process*/
    shmdt(shmptr);

    /* Delete shared memory*/
    shmctl(shmid, IPC_RMID, NULL);
    printf("Shared memory deleted\n");
    return 0;
}
