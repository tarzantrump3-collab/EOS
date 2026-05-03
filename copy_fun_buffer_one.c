#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

    int fd = open("file.txt", O_RDONLY);

        int fd_write = open("file3.txt",  O_WRONLY | O_CREAT,0644);

        if (fd < 0 || fd_write < 0)
    {
        perror("Error opening file");
        return 1;
    }

    char buffer;
    int ret;

    while ((ret = read(fd, &buffer, 1) > 0))
    {
	write( 1 , &buffer, 1);
	sleep(1);
        write(fd_write, &buffer,1);
    }

    if (ret < 0)
        perror("Error reading file");

    close(fd);
    return 0;
}
 while ((ret = read(fd, buffer, sizeof(buffer))) > 0)
    {

        write(fd_write, buffer, ret);
    }

    if (ret < 0)
        perror("Error reading file");


