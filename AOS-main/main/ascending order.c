// Write a C program which receives file names as command line arguments and display those
// filenames in ascending order according to their sizes. I) (e.g $ a.out a.txt b.txt c.txt, …)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    char *filename;
    off_t size; // File size
} FileInfo;

// Comparison function for sorting
int compare(const void *a, const void *b) {
    FileInfo *fileA = (FileInfo *)a;
    FileInfo *fileB = (FileInfo *)b;
    return (fileA->size - fileB->size);
}

int main(int argc, char *argv[]) {
    int i;
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    FileInfo *files = malloc((argc - 1) * sizeof(FileInfo));
    if (files == NULL) {
        perror("malloc");
        return 1;
    }

    // Get sizes of the files
    for (i = 1; i < argc; i++) {
        struct stat fileStat;
        if (stat(argv[i], &fileStat) == -1) {
            perror(argv[i]);
            free(files);
            continue; // Skip this file if it doesn't exist or can't be accessed
        }
        files[i - 1].filename = argv[i];
        files[i - 1].size = fileStat.st_size;
    }

    // Sort the files based on size
    qsort(files, argc - 1, sizeof(FileInfo), compare);

    // Display the filenames in ascending order according to their sizes
    printf("Files sorted by size (ascending order):\n");
    for ( i= 0; i < argc - 1; i++) {
        printf("%s: %ld bytes\n", files[i].filename, files[i].size);
    }

    free(files);
    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out file1.txt file2.txt
// Files sorted by size (ascending order):
// file1.txt: 0 bytes
// file2.txt: 0 bytes
