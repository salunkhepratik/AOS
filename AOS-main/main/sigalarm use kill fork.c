// Write a C program to send SIGALRM signal by child process to parent process and parent process
// make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep
// system call)

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signo) {
    printf("Alarm is fired!\n");
}

int main() {
    pid_t pid;

    // Set signal handler for SIGALRM
    if (signal(SIGALRM, signal_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    // Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) { // Child process
        // Send SIGALRM signal to parent process
        kill(getppid(), SIGALRM);
        printf("Child process sent signal to parent.\n");
    } else { // Parent process
        printf("Parent process waiting for signal...\n");
        pause(); // Wait for signal to be received
    }
    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out 
// Parent process waiting for signal...
// Child process sent signal to parent.
// Alarm is fired!
