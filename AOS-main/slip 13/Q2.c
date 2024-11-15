// Write a C program that a string as an argument and return all the files that begins with that name
// in the current directory. For example > ./a.out foo will return all file names that begins with foo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    const char *prefix = argv[1];
    DIR *directory;
    struct dirent *entry;

    // Open the current directory
    directory = opendir(".");
    if (directory == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Files starting with '%s':\n", prefix);
    // Read entries in the directory
    while ((entry = readdir(directory)) != NULL) {
        // Check if the filename starts with the given prefix
        if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(directory);
    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out file
// Files starting with 'file':
// file2.txt
// file1.txt
