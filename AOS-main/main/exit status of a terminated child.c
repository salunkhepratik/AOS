// Write a C program that print the exit status of a terminated child process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Create a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Simulate some work in the child process
        printf("Child process is running...\n");
        sleep(2); // Sleep for 2 seconds
        exit(42); // Exit with a status code of 42
    } else { // Parent process
        // Wait for the child process to terminate
        waitpid(pid, &status, 0);

        // Check if the child terminated normally
        if (WIFEXITED(status)) {
            // Retrieve the exit status of the child
            int exit_status = WEXITSTATUS(status);
            printf("Child process terminated with exit status: %d\n", exit_status);
        } else {
            printf("Child process did not terminate normally.\n");
        }
    }

    return 0;
}

// [smile@localhost slip os 6sem]$ ./a.out 
// Child process is running...
// Child process terminated with exit status: 42
