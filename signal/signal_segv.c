#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void segfault_handler(int sig);

void main(){
	printf("^SIGSEGV\n");
	signal(SIGSEGV, segfault_handler);
	
	printf("below of trigger function\n");
	int *p = NULL;
	*p = 10; //this tigger the SIGSEGV
	printf("access invalid memory\n");

	return;

}

void segfault_handler(int sig){
	printf("error :segmentation fault (signal %d ) detected\n",sig);
	printf("cleaning up and existing safely ....\n");
	exit(1); 
}
