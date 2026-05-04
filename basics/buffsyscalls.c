#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *src = fopen(argv[1], "rb");
    FILE *dest = fopen(argv[2], "wb");
    char buffer;

    while (fread(&buffer, 1, 1, src) == 1) {
        fwrite(&buffer, 1, 1, dest);
    }

    fclose(src);
    fclose(dest);
    return 0;
}
