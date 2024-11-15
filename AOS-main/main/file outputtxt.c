// Write a C program that redirects standard output to a file output.txt. (use of dup and open system call).

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file "output.txt" with write permissions. If it doesn't exist, create it.
    int file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0) {
        perror("Failed to open output.txt");
        exit(1);
    }

    // Duplicate the file descriptor for "output.txt" onto the standard output file descriptor (1).
    if (dup2(file, STDOUT_FILENO) < 0) {
        perror("Failed to redirect standard output");
        close(file);
        exit(1);
    }

    // Close the original file descriptor as it's no longer needed.
    close(file);

    // Now, any output to standard output (printf) will be redirected to "output.txt".
    printf("This message will be written to output.txt instead of the console.\n");
    printf("Another line in the file.\n");

    return 0;
}
