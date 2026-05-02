

#include <stdio.h>       // Library for standard Input/Output (printf, perror)
#include <stdlib.h>      // Library for general functions (exit)
#include <unistd.h>      // The "sacrosanct" header for POSIX system calls (fork, exec)
#include <sys/wait.h>    // Library containing the wait() system call for process sync

int main() {
    pid_t pid; 

    // Step 1: Create a clone of the current process
    pid = fork();

    
    if (pid < 0) {
        perror("Fork failed"); 
        exit(1); 
    } 
    else if (pid == 0) {
        // --- CHILD PROCESS SCOPE ---
         
        printf("[Child] My PID is %d. Loading 'date' command...\n", getpid());

        // Step 2: REPLACE the child's memory with a new program
        char *args[] = {"date", NULL};
        execvp(args[0], args);
        
        perror("exec failed");
        exit(1);
    } 
    else {
        // --- PARENT PROCESS SCOPE ---
        
        printf("[Parent] I am process %d. My child is %d.\n", getpid(), pid);

        // Step 3: Synchronization
        // The parent voluntarily yields the CPU and waits for the child to finish
        // This prevents the child from becoming an "orphan"
        wait(NULL); 

        printf("[Parent] Child has finished execution. Parent resuming...\n");
    }

    return 0; 
}

