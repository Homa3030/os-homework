#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd = open("./ex1.txt", O_RDWR);
    struct stat stats;
    fstat(fd, &stats);

    char * mem = mmap(0, stats.st_size, PROT_WRITE, MAP_SHARED, fd, 0);

    ftruncate(fd, strlen("This is a nice day"));
    strcpy(mem, "This is a nice day");

    close(fd);

    return 0;
}