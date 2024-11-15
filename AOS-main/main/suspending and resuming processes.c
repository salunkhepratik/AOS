// Write a C program that illustrates suspending and resuming processes using signals

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum) {
    // This handler is intentionally left empty.
    // It just prevents the child from terminating immediately.
}

int main() {
    pid_t pid;
    int count = 0;

    // Set up signal handler for the child process
    signal(SIGUSR1, handler); // To catch SIGUSR1 and do nothing

    // Create a child process
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        while (1) {
            printf("Child counting: %d\n", count++);
            sleep(1); // Sleep for a second
        }
    } else { // Parent process
        sleep(3); // Let the child count for 3 seconds

        printf("Parent: Suspending child process...\n");
        kill(pid, SIGSTOP); // Suspend the child process
        sleep(5); // Wait for 5 seconds while the child is suspended

        printf("Parent: Resuming child process...\n");
        kill(pid, SIGCONT); // Resume the child process

        // Allow the child to run for a few more seconds before terminating
        sleep(5);
        
        // Terminate the child process
        printf("Parent: Terminating child process...\n");
        kill(pid, SIGTERM);
        wait(NULL); // Wait for the child to terminate
        printf("Parent: Child process terminated.\n");
    }

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out 
// Child counting: 0
// Child counting: 1
// Child counting: 2
// Parent: Suspending child process...
// Parent: Resuming child process...
// Child counting: 3
// Child counting: 4
// Child counting: 5
// Child counting: 6
// Child counting: 7
// Parent: Terminating child process...
// Parent: Child process terminated.
