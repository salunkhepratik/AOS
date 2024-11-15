// Display all the files from current directory which are created in particular month

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void display_files_in_month(const char *month_name) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    // Open current directory
    if ((dir = opendir(".")) == NULL) {
        perror("Unable to open directory");
        return;
    }

    printf("Files created/modified in %s:\n", month_name);

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Only regular files
            if (stat(entry->d_name, &file_stat) == -1) {
                perror("stat failed");
                continue;
            }

            struct tm *timeinfo = localtime(&file_stat.st_mtime);
            char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

            if (strcmp(months[timeinfo->tm_mon], month_name) == 0) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir); // Close the directory
}

int main() {
    char month[4];

    // Get the month from user
    printf("Enter the month (e.g., Jan, Feb, ...): ");
    scanf("%3s", month);

    // Display files modified in the specified month
    display_files_in_month(month);

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out
// Enter the month (e.g., Jan, Feb, ...): Oct
// Files created/modified in Oct:
// q1.c
// file2.txt
// file1.txt
// a.out
