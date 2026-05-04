#include <stdio.h>
#include <unistd.h> // for sleep()

int main() {
    printf("Loading: ");

    for (int i = 0; i < 10; i++) {
        printf(".");    // This goes into the buffer, but NOT the screen yet
        
        // 1. Try commenting this line out to see the difference:
        fflush(stdout); // Forces the "." out of the buffer to the terminal
        
        sleep(1);       // Wait 1 second
    }

    printf(" Done!\n");
    return 0;
}
