#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main()
{
    int shmid;
    char *shmptr;

    /*
     * Connect to existing shared memory
     */
    shmid = shmget(SHM_KEY,
                   SHM_SIZE,
                   0666);

    if(shmid < 0) {
        perror("shmget");
        return -1;
    }

    printf("Connected Shared Memory ID : %d\n", shmid);

    /*
     * Attach shared memory
     */
    shmptr = shmat(shmid, NULL, 0);

    if(shmptr == (void *)-1) {
        perror("shmat");
        return -1;
    }

    printf("Attached at : %p\n", shmptr);

    /*
     * Read directly from shared memory
     */
    printf("Received Data : %s\n", shmptr);

    /*
     * Detach
     */
    shmdt(shmptr);

    return 0;
}
