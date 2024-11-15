// Write a C program which creates a child process to run linux/ unix command or any user defined
// program. The parent process set the signal handler for death of child signal and Alarm signal. If
// a child process does not complete its execution in 5 second then parent process kills child process.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t child_pid; // Global variable to hold the child process ID

// Signal handler for SIGCHLD (child termination)
void handle_sigchld(int sig) {
	int errno;
    int saved_errno = errno;
    while (waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno; // Restore errno
}

// Signal handler for SIGALRM
void handle_sigalrm(int sig) {
    printf("\nChild process did not complete in 5 seconds. Killing child process (PID: %d)...\n", child_pid);
    kill(child_pid, SIGKILL); // Kill the child process
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // Set up signal handlers
    signal(SIGCHLD, handle_sigchld);
    signal(SIGALRM, handle_sigalrm);

    // Fork the process to create a child
    child_pid = fork();

    if (child_pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process (PID: %d) is executing the command: %s\n", getpid(), argv[1]);
        
        // Execute the command passed as argument
        execvp(argv[1], &argv[1]);

        // If execvp returns, it means there was an error
        perror("exec failed");
        exit(1);
    } else {
        // Parent process
        alarm(5); // Set an alarm for 5 seconds

        // Wait for the child process to terminate
        while (1) {
            pause(); // Wait for signals
        }
    }

    return 0;
}



// [smile@localhost slip os 6sem]$ ./a.out sleep 10
// Child process (PID: 6374) is executing the command: sleep

// Child process did not complete in 5 seconds. Killing child process (PID: 6374)...
