
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

    int fd = open("one_byte_each.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }
    for (int i = 0; i < 10; i++) {
        char byte = 'A' ;
        write(fd, &byte, 1);
    }
    close(fd);
    return 0;
}
