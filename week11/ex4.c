#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define IN_FILE_PATH "./ex1.txt"
#define OUT_FILE_PATH "./ex1.memcpy.txt"

int main() {
    int fdin = open(IN_FILE_PATH, O_RDONLY);
    int fdout = open(OUT_FILE_PATH, O_RDWR);

    struct stat in_stats, out_stats;
    fstat(fdin, &in_stats);
    fstat(fdout, &out_stats);

    ftruncate(fdout, in_stats.st_size);

    void * memin = mmap(0, in_stats.st_size, PROT_READ, MAP_SHARED, fdin, 0);
    void * memout = mmap(0, in_stats.st_size, PROT_WRITE, MAP_SHARED, fdout, 0);

    
    memcpy(memout, memin, in_stats.st_size);

    close(fdin);
    close(fdout);

    return 0;
}