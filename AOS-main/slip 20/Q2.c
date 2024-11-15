// Write a C program to Identify the type (Directory, character device, Block device, Regular file,
// FIFO or pipe, symbolic link or socket) of given file using stat() system call.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) < 0) {
        perror("stat");
        return 1;
    }

    if (S_ISREG(fileStat.st_mode)) {
        printf("%s is a regular file.\n", argv[1]);
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("%s is a directory.\n", argv[1]);
    } else if (S_ISCHR(fileStat.st_mode)) {
        printf("%s is a character device.\n", argv[1]);
    } else if (S_ISBLK(fileStat.st_mode)) {
        printf("%s is a block device.\n", argv[1]);
    } else if (S_ISFIFO(fileStat.st_mode)) {
        printf("%s is a FIFO/pipe.\n", argv[1]);
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("%s is a symbolic link.\n", argv[1]);
    } else if (S_ISSOCK(fileStat.st_mode)) {
        printf("%s is a socket.\n", argv[1]);
    } else {
        printf("%s is of unknown type.\n", argv[1]);
    }

    return 0;
}

// [smile@localhost slip os 6sem]$ ./a.out file1.txt 
// file1.txt is a regular file.
