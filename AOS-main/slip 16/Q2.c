// Write a C program which create a child process which catch a signal sighup, sigint and sigquit.
// The Parent process send a sighup or sigint signal after every 3 seconds, at the end of 30 second
// parent send sigquit signal to child and child terminates my displaying message “My DADDY has
// Killed me!!!”.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void handle_sighup(int sig) {
    printf("Child received SIGHUP signal.\n");
}

void handle_sigint(int sig) {
    printf("Child received SIGINT signal.\n");
}

void handle_sigquit(int sig) {
    printf("My DADDY has Killed me!!!\n");
    exit(0); // Exit the child process
}

int main() {
    pid_t child_pid = fork(); // Create a child process

    if (child_pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        // Set up signal handlers
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        // Infinite loop to keep the child process running
        while (1) {
            pause(); // Wait for signals
        }
    } else {
        // Parent process
        for (int i = 0; i < 10; i++) {
            sleep(3); // Wait for 3 seconds
            if (i < 4) {
                // Send SIGHUP or SIGINT
                if (i % 2 == 0) {
                    kill(child_pid, SIGHUP); // Send SIGHUP on even iterations
                } else {
                    kill(child_pid, SIGINT); // Send SIGINT on odd iterations
                }
            }
        }

        // After 15 seconds, send SIGQUIT
        sleep(3); // Wait another 3 seconds before sending SIGQUIT
        kill(child_pid, SIGQUIT); // Send SIGQUIT

        // Wait for the child process to terminate
        wait(NULL); // Clean up the child process
    }

    return 0;
}



// Child received SIGHUP signal.
// Child received SIGINT signal.
// Child received SIGHUP signal.
// Child received SIGINT signal.
// Child received SIGHUP signal.
// My Papa has Killed me!!!
