
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

    int fd = open("file.txt", O_RDONLY);

    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    char buffer[100];
    int ret;


    while ((ret = read(fd, buffer, sizeof(buffer))) > 0)
    {
   			sleep(1);
        write(1, buffer, ret);
    }

    if (ret < 0) 
        perror("Error reading file");

    close(fd);
    return 0;
}
