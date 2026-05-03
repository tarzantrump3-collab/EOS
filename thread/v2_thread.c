#include<stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_routine(void *arg);


int counter =0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void main(){
	int main_st =10;
	int ret, arg[2];
	pthread_t thread1, thread2;

	arg[0] =1;
	ret = pthread_create(&thread1, NULL, thread_routine, (arg +0));
	if(ret != 0){
		printf("thread1 creat error: %d \n", ret);
 		return;
	}

	arg[1] =2;
        ret = pthread_create(&thread2, NULL, thread_routine, (void*)(arg +1));
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


	printf("main counter = %d\n",counter);



}

void *thread_routine(void *arg){
	// 10 lakh
	 for(int i = 0; i<10000; i++){
		++counter;
	 }
	 pthread_exit(NULL);
}
