// Display all the files from current directory whose size is greater that n Bytes Where n is accept from user.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    long n;

    // Accept the size limit from the user
    printf("Enter the size limit (in bytes): ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid number.\n");
        return 1;
    }

    DIR *directory;
    struct dirent *entry;
    struct stat fileStat;

    // Open the current directory
    directory = opendir(".");
    if (directory == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Files larger than %ld bytes:\n", n);
    // Read entries in the directory
    while ((entry = readdir(directory)) != NULL) {
        // Ignore "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get file stats
        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        // Check if the file size is greater than n
        if (fileStat.st_size > n) {
            printf("%s: %ld bytes\n", entry->d_name, fileStat.st_size);
        }
    }

    // Close the directory
    closedir(directory);
    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out 
// Enter the size limit (in bytes): 8
// Files larger than 8 bytes:
// q1.c: 1356 bytes
// output.txt: 78 bytes
// a.out: 8880 bytes
