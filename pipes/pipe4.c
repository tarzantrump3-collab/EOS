//fifo

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#define FIFO_NAME "/tmp/myfifo"


int main() {
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    char buffer[100], str[100];
    int fd1;

    while(1)
    {
        fd1  = open(myfifo, O_WRONLY);
        printf("Enter a message to send : ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;
        write(fd1, str, strlen(str) + 1);
        close(fd1);
        fd1  = open(myfifo, O_RDONLY);
        read(fd1, buffer, sizeof(buffer));
        printf("Received: %s\n", buffer);
        close(fd1);

    }

    return 0;
}
