  
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define DIR_TO_CHECK "./tmp"
#define STRING_SIZE 128
#define BUFFER_SIZE 16

char file_names[STRING_SIZE][BUFFER_SIZE];
ino_t inodes[BUFFER_SIZE];
size_t found_files_count;

char full_name[STRING_SIZE];

ino_t processed[BUFFER_SIZE];
size_t processed_count;

void print_all_files(ino_t inode) {
    for (size_t i = 0; i < found_files_count; i++)
    {
        if (inodes[i] != inode) {
            continue;
        }

        printf("%s %lu\n", file_names[i], inodes[i]);
    }
}

int has_two_or_more_files(ino_t inode) {
    size_t count = 0;

    for (size_t i = 0; i < found_files_count; i++)
    {
        if (inodes[i] == inode) {
            count++;
            if (count == 2) {
                return 1;
            }
        }
    }

    return 0;
}

int is_already_processed(ino_t inode) {
    for (size_t i = 0; i < processed_count; i++)
    {
        if (processed[i] == inode) {
            return 1;
        }
    }

    return 0;
}

void mark_as_processed(ino_t inode) {
    processed[processed_count++] = inode;
}

void scan_directory(DIR * dirp) {
    struct dirent * dp;
    struct stat stats;

    while ((dp = readdir(dirp)) != NULL) {
        full_name[0] = '\0';
        strcat(full_name, DIR_TO_CHECK "/");
        strcat(full_name, dp->d_name);

        if (stat(full_name, &stats) != 0) {
            printf("error with %s\n", full_name);
            continue;
        }

        inodes[found_files_count] = stats.st_ino;
        strcpy(file_names[found_files_count], dp->d_name);

        found_files_count++;
    }
}

void print_all_inodes_with_two_or_more_files() {
    ino_t inode;

    printf("Nodes with two or more nodes:\n");

    for (size_t i = 0; i < found_files_count; i++)
    {
        inode = inodes[i];

        if (is_already_processed(inode)) {
            continue;
        }

        if (has_two_or_more_files(inode)) {
            print_all_files(inode);
            mark_as_processed(inode);
        }
    }
}

int main() {
    DIR * dirp = opendir(DIR_TO_CHECK);

    if (dirp == NULL) {
        printf("Directory not found.");
        return -1;
    }

    scan_directory(dirp);
    closedir(dirp);
    print_all_inodes_with_two_or_more_files();

    return 0;
}