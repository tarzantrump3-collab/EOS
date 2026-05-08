#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main() {
    int p[2];
    pid_t pid;

    pipe(p);
    pid = fork();

    if (pid > 0) {
        close(p[0]);
        FILE *file = fopen("test.txt", "r");
        if (file == NULL) {
            perror("File error");
            return 1;
        }

        char ch;
        while ((ch = fgetc(file)) != EOF) {
            write(p[1], &ch, 1);
        }

        fclose(file);
        close(p[1]);
    } 
    else {
        close(p[1]);
        char ch;
        int lines = 0, words = 0, chars = 0;
        int in_word = 0;

        while (read(p[0], &ch, 1) > 0) {
            chars++;
            
            if (ch == '\n') {
                lines++;
            }

            if (isspace(ch)) {
                in_word = 0;
            } else if (in_word == 0) {
                in_word = 1;
                words++;
            }
        }

        printf("Lines: %d\n", lines);
        printf("Words: %d\n", words);
        printf("Characters: %d\n", chars);

        close(p[0]);
        exit(0);
    }

    return 0;
}
