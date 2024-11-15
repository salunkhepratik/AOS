// Write a C program to create an unnamed pipe. The child process will write following three
// messages to pipe and parent process display it.
// Message1 = “Hello World”
// Message2 = “Hello SPPU”
// Message3 = “Linux is Funny”

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[100];
    
    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Close the read end of the pipe
        close(pipefd[0]);

        // Write messages to the pipe
        write(pipefd[1], "Hello World\n", strlen("Hello World\n"));
        write(pipefd[1], "Hello SPPU\n", strlen("Hello SPPU\n"));
        write(pipefd[1], "Linux is Funny\n", strlen("Linux is Funny\n"));

        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    } else { // Parent process 
        // Close the write end of the pipe
        close(pipefd[1]);

        // Read messages from the pipe
        while (read(pipefd[0], buffer, sizeof(buffer)) > 0) {
            printf("%s", buffer);
        }

        close(pipefd[0]);
    }

    return 0;
}

// [smile@localhost slip os 6sem]$ ./a.out
// Hello World
// Hello SPPU
// Linux is Funny
