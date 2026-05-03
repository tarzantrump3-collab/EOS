
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {

    int fd = open("all_in_one.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }
   char buffer[10];
   memset(buffer, 'A', sizeof(buffer));
   write(fd, buffer, sizeof(buffer));
    
    close(fd);
    return 0;
}
