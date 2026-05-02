
#include <stdio.h>       // Library for standard Input/Output (printf, perror)
#include <stdlib.h>      // Library for general functions (exit)
#include <unistd.h>      // The "sacrosanct" header for POSIX system calls (fork, exec)
#include <sys/wait.h>    // Library containing the wait() system call for process sync

int main() {
    // pid_t is a special data type for Process IDs, ensuring architectural portability
    pid_t pid; 

    // Step 1: Create a clone of the current process
    // This single line creates a second, identical execution environment
    pid = fork();

    // After fork(), the code splits. Two processes are now running this line.
    
    if (pid < 0) {
        // SCENARIO: The Kernel failed to create a new process (e.g., out of memory)
        perror("Fork failed"); 
        exit(1); 
    } 
    else if (pid == 0) {
        // --- CHILD PROCESS SCOPE ---
        // fork() returns 0 to the child to tell it "You are the newborn"
        
        printf("[Child] My PID is %d. Loading 'date' command...\n", getpid());

        // Step 2: REPLACE the child's memory with a new program
        // execvp looks for "date" in the system PATH and transforms the child
        char *args[] = {"date", NULL};
        execvp(args[0], args);
        
        // CRITICAL: If execvp succeeds, the code below is NEVER executed
        // because the child's code segment has been replaced.
        perror("exec failed");
        exit(1);
    } 
    else {
        // --- PARENT PROCESS SCOPE ---
        // fork() returns the Child's actual PID to the parent (a positive integer)
        
        printf("[Parent] I am process %d. My child is %d.\n", getpid(), pid);

        // Step 3: Synchronization
        // The parent voluntarily yields the CPU and waits for the child to finish
        // This prevents the child from becoming an "orphan"
        wait(NULL); 

        printf("[Parent] Child has finished execution. Parent resuming...\n");
    }

    // Both processes eventually reach their respective exits
    return 0; 
}
;