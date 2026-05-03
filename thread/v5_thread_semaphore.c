#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

//void *thread_routine(void *arg);
void *thread_A(void *arg);
void *thread_B(void *arg);

int counter =0;
int fd;
int val_b2a, val_a2b;


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sig_a2b, sig_b2a;

//sem_getvalue(&sig_b2a, &val_b2a);
//sem_getvalue(&sig_a2b, &val_a2b);


void main(){

	int main_st =10;
	int ret, arg[2];
	pthread_t thread1, thread2;
	
	ret = sem_init(&sig_a2b, 0, 0);
	
	if(ret != 0)  perror("sig_a2b create error");
	
	ret = sem_init(&sig_b2a, 0, 1);
	

//	sem_getvalue(&sig_b2a, &val_b2a);
//	sem_getvalue(&sig_a2b, &val_a2b);


	if(ret != 0) perror("sig_b2a create error");
	
	
	fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

      	if(fd == -1) {
		perror("open failed");
		return;

		// fail check of file
	}

	arg[0] =1;
	ret = pthread_create(&thread1, NULL, thread_A, (arg +0));
	if(ret != 0){
		printf("thread1 creat error: %d \n", ret);
 		return;
	}

	arg[1] =2;
        ret = pthread_create(&thread2, NULL, thread_B, (void*)(arg +1));
        if(ret != 0){
                printf("thread2 creat error: %d \n", ret);
                return;
        }

	ret = pthread_join(thread1, NULL);
	if(ret != 0){
		printf("thread1 join erreo\n");
		return;
	}
	printf("thread 2 exited , main continues\n");

	ret = pthread_join(thread2, NULL);
        if(ret != 0){
                printf("thread2 join erreo\n");
                return;
        }
        printf("thread 1 exited , main continues\n");


	pthread_mutex_destroy(&lock);



}

void *thread_A(void *arg){
	//pthread_mutex_lock(&lock);
	for(int i = 0; i<100; i++){
		sem_wait(&sig_b2a);
        sem_getvalue(&sig_b2a, &val_b2a);
        sem_getvalue(&sig_a2b, &val_a2b);

	//	pthread_mutex_lock(&lock);
	 	 printf("	  A->sig_b2a = %d sig_a2b = %d\n", val_b2a, val_a2b);
		 write(fd,"AAAAA",5);
		 sleep(1);
		 write(1, "AAAAA",5);
		 sleep(1);
		 sem_post(&sig_a2b);
        sem_getvalue(&sig_b2a, &val_b2a);
        sem_getvalue(&sig_a2b, &val_a2b);

		 printf("    :A->sig_b2a = %d sig_a2b = %d\n", val_b2a, val_a2b);

	//	 pthread_mutex_unlock(&lock);
	 }
	//pthread_mutex_unlock(&lock);
	 pthread_exit(NULL);
}

void *thread_B(void *arg){
               
        for(int i = 0; i<100; i++){
		sem_wait(&sig_a2b);
        sem_getvalue(&sig_b2a, &val_b2a);
        sem_getvalue(&sig_a2b, &val_a2b);

       //         pthread_mutex_lock(&lock);
       		printf("	 B-> sig_b2a = %d sig_a2b = %d\n", val_b2a, val_a2b);
                 write(fd,"BBBBB",5);
		 sleep(1);
		 write(1,"BBBBB", 5);
		 sleep(1);
         //        pthread_mutex_unlock(&lock);
	        sem_post(&sig_b2a);

	sem_getvalue(&sig_b2a, &val_b2a);
        sem_getvalue(&sig_a2b, &val_a2b);

	printf("    B-> sig_b2a = %d sig_a2b = %d\n", val_b2a, val_a2b);

	}
        
         pthread_exit(NULL);
}
