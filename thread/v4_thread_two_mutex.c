#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//void *thread_routine(void *arg);
void *thread_A(void *arg);
void *thread_B(void *arg);

int counter =0;
int fd;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;



void main(){

	int main_st =10;
	int ret, arg[2];
	pthread_t thread1, thread2;
	


	fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

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






}

void *thread_A(void *arg){
	// 10 lakh
	//pthread_mutex_lock(&lock);
	for(int i = 0; i<100; i++){
		pthread_mutex_lock(&lock);
	 	 write(fd,"AAAAA",5);
		 pthread_mutex_unlock(&lock);
	 }
	//pthread_mutex_unlock(&lock);
	 pthread_exit(NULL);
}

void *thread_B(void *arg){
        // 10 lakh
        
        for(int i = 0; i<100; i++){
                pthread_mutex_lock(&lock);
                 write(fd,"BBBBB",5);
                 pthread_mutex_unlock(&lock);
         }
        
         pthread_exit(NULL);
}
