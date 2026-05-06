#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void timer_handler(int signum)
{
    printf("alarm signal %d received\n", signum);
}

int main()
{
    signal(SIGALRM, timer_handler);
    printf("Setting alarm for 5 seconds...\n");
    alarm(5);

    printf("Waiting for alarm signal...\n");
    pause(); // Wait for signal

    printf("Alarm signal handled, exiting now.\n");
    return 0;
}
