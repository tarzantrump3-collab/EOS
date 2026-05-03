#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

    int fd = open("file.txt", O_RDONLY);

        int fd_write = open("file3.txt",  O_WRONLY | O_CREAT,0644);

        if (fd < 0)
    {
        perror("Error opening file 1");
        return 1;
    }


    if (fd_write < 0)
    {
        perror("Error opening file 2");
        return 1;
    }

    char buffer[100];
    int ret;


    while ((ret = read(fd, buffer, sizeof(buffer))) > 0)
    {

        write(fd_write, buffer, ret);
    }

    if (ret < 0)
        perror("Error reading file");

    close(fd);
    close(fd_write);
    return 0;
}
 