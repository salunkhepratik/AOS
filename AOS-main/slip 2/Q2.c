// Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the
// appropriate message and exits on pressing ctrl-c again.


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int sigint_count = 0;

void sigint_handler(int sig) {
    if (sigint_count == 0) {
        printf("\nCtrl+C pressed once. Press again to exit.\n");
        sigint_count++;
    } else {
        printf("\nExiting...\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, sigint_handler);

    while (1) {
        // Your program logic here
        printf("Working...\n");
        sleep(1);
    }

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out 
// Working...
// Working...
// ^C
// Ctrl+C pressed once. Press again to exit.
// Working...
// ^C
// Exiting...
