#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void main(){
	signal(SIGSEGV, segfault_handler);

	int *p + NULL;
	*p = 10; //this tigger the SIGEGV

	return;

}

void segfault_handler(int sig){
	printf("error :segmentation fault (signal %d ) deced\n",sig);
	printf("cleaning up and existing safely ....\n");
	exit(1); 
}
