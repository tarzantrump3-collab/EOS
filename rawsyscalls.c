#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int src = open(argv[1], O_RDONLY);
    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buffer;

    while (read(src, &buffer, 1) > 0) {
        write(dest, &buffer, 1);
    }

    close(src);
    close(dest);
    return 0;
}
