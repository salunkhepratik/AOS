// Implement the following unix/linux command (use fork, pipe and exec system call)
// ls –l | wc –l


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child process for 'ls -l'
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { // Child process 1
        // Close unused write end
        close(pipefd[1]);

        // Redirect stdout to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // Close original read end

        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);
        perror("execlp"); // Only reached if exec fails
        exit(EXIT_FAILURE);
    }

    // Fork the second child process for 'wc -l'
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { // Child process 2
        // Close unused read end
        close(pipefd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // Close original write end

        // Execute 'wc -l'
        execlp("wc", "wc", "-l", NULL);
        perror("execlp"); // Only reached if exec fails
        exit(EXIT_FAILURE);
    }

    // Parent process
    // Close both ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out 
// total 20
// -rwxrwxr-x. 1 smile smile 8712 Oct 21 09:01 a.out
// -rwxrw-rw-. 1 smile smile    0 Oct 21 07:49 file1.txt
// -rwxrw-rw-. 1 smile smile    0 Oct 21 07:49 file2.txt
// -rw-rw-r--. 1 smile smile  112 Oct 21 08:58 output.txt
// -rw-rw-r--. 1 smile smile 1709 Oct 21 09:01 q1.c
