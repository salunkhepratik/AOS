// Take multiple files as Command Line Arguments and print their inode numbers and file types


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
int i;
    for ( i= 1; i < argc; i++) {
        struct stat fileStat;
        if (stat(argv[i], &fileStat) == -1) {
            perror("stat");
            continue;
        }

        printf("File: %s\n", argv[i]);
        printf("Inode: %lu\n", fileStat.st_ino);

        switch (fileStat.st_mode & S_IFMT) {
            case S_IFREG:  printf("Type: Regular file\n"); break;
            case S_IFDIR:  printf("Type: Directory\n"); break;
            case S_IFCHR:  printf("Type: Character device\n"); break;
            case S_IFBLK:  printf("Type: Block device\n"); break;
            case S_IFIFO:  printf("Type: FIFO/pipe\n"); break;
            case S_IFLNK:  printf("Type: Symbolic link\n"); break;
            case S_IFSOCK: printf("Type: Socket\n"); break;
            default:       printf("Type: Unknown\n"); break;
        }
        printf("\n");
    }

    return 0;
}



// gcc Q1.c
// ./a.out file1.txt file2.txt 
