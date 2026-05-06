#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int count = 0;

void handler(int signum)
{
    printf("Signal received: %d\n im not closing yet.\n", signum);
    ++count;
    if(count == 3)
    {
        printf("Received signal 3 times,assign default handler exiting now.\n");
        signal(SIGINT, SIG_DFL);
    }
}

int main()
{
    signal(SIGINT, handler);
    while(1)
    {
        printf("sleeping...try pressing Ctrl+C\n");
        sleep(1);
    }
    return 0;
}
