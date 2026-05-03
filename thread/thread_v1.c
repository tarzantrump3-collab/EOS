#include<stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_routine(void *arg);

int glob_dat = 10;
int glob_bss;


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
	printf("thread 2 exir=ted , main continues\n");

	ret = pthread_join(thread2, NULL);
        if(ret != 0){
                printf("thread2 join erreo\n");
                return;
        }
        printf("thread 1 exir=ted , main continues\n");




}

void *thread_routine(void *arg){
	printf("arg: %p\n",arg);

	if(arg == NULL){
		printf("argument null\n");
		pthread_exit(NULL);
	}
	int a = *(int *) arg;
	while(1){
		printf("thread %d, data : %d ,bss: %d \n",a,glob_dat, glob_bss);
		
		if(a == 1) {
			++glob_dat;
		} else if (a == 2){
			--glob_dat;
		}
		sleep(1);
	}
}
