// Write a C program to create n child processes. When all n child processes terminates, Display
// total cumulative time children spent in user and kernel mode

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>

void child_process(int id) {
    // Simulate some work in the child process
    printf("Child %d is running...\n", id);
    for (volatile long i = 0; i < 100000000; i++); // Busy-wait to consume CPU time
    printf("Child %d finished.\n", id);
    exit(0); // Child process terminates
}

int main() {
    int n;
    printf("Enter the number of child processes: ");
    scanf("%d", &n);

    pid_t pid;
    struct tms tbuf;
    clock_t start, end;
    long total_user_time = 0;
    long total_system_time = 0;

    for (int i = 0; i < n; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }
        if (pid == 0) {
            child_process(i); // Child process
        }
    }

    // Parent process
    for (int i = 0; i < n; i++) {
        wait(&pid); // Wait for all child processes to finish
        // Get times for the terminated child process
        times(&tbuf);
        total_user_time += tbuf.tms_utime;   // User time of the child
        total_system_time += tbuf.tms_stime; // System time of the child
    }

    printf("Total cumulative time spent by children:\n");
    printf("User Mode: %ld clock ticks\n", total_user_time);
    printf("Kernel Mode: %ld clock ticks\n", total_system_time);

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out
// Enter the number of child processes: 5
// Child 0 is running...
// Child 2 is running...
// Child 1 is running...
// Child 3 is running...
// Child 4 is running...
// Child 0 finished.
// Child 2 finished.
// Child 3 finished.
// Child 1 finished.
// Child 4 finished.
// Total cumulative time spent by children:
// User Mode: 0 clock ticks
// Kernel Mode: 0 clock ticks
