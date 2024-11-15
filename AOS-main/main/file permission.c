// Write a C program to find file properties such as inode number, number of hard link, File
// permissions, File size, File access and modification time and so on of a given file using stat()
// system call.



#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) < 0) {
        perror("stat");
        return 1;
    }

    printf("File: %s\n", argv[1]);

    // Inode number
    printf("Inode number: %ld\n", fileStat.st_ino);

    // Number of hard links
    printf("Number of hard links: %ld\n", fileStat.st_nlink);

    // File permissions
    printf("File permissions: ");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // File size
    printf("File size: %ld bytes\n", fileStat.st_size);

    // File access time
    printf("Last access time: %s", ctime(&fileStat.st_atime));

    // File modification time
    printf("Last modification time: %s", ctime(&fileStat.st_mtime));

    // File status change time
    printf("Last status change time: %s", ctime(&fileStat.st_ctime));

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out file1.txt 
// File: file1.txt
// Inode number: 34108534
// Number of hard links: 1
// File permissions: -rwxrw-rw-
// File size: 0 bytes
// Last access time: Mon Oct 21 07:51:03 2024
// Last modification time: Mon Oct 21 07:49:38 2024
// Last status change time: Mon Oct 21 07:51:03 2024
