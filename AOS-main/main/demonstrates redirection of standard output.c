// Write a C Program that demonstrates redirection of standard output to a file

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open a file for writing, redirecting stdout to this file
    FILE *file = freopen("output.txt", "w", stdout);
    
    // Check if the file redirection was successful
    if (file == NULL) {
        perror("Error redirecting output");
        return EXIT_FAILURE;
    }

    // This output will go to output.txt instead of the console
    printf("Hello, World!\n");
    printf("This is an example of output redirection.\n");
    printf("All this text will be written to the file 'output.txt'.\n");

    // Close the file (though it will be closed automatically on exit)
    fclose(file); // Not necessary, but good practice

    return EXIT_SUCCESS;
}
