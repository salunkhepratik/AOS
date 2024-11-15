// Generate parent process to write unnamed pipe and will read from it

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2]; // Array to hold the pipe file descriptors
    pid_t pid;
    char buffer[100]; // Buffer for reading data from the pipe
    const char *message = "Hello from the parent process!";

    // Create the unnamed pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        // Write message to the pipe
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]); // Close the write end of the pipe after writing

        // Optionally, wait for the child to finish (not necessary here)
        wait(NULL);
    } else { // Child process
        close(pipefd[1]); // Close the write end of the pipe

        // Read message from the pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipefd[0]); // Close the read end of the pipe after reading
    }

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out 
// Child received: Hello from the parent process!
