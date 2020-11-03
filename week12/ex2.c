#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_STREAMS_NUMBER 10
#define BUFFER_SIZE 64

FILE * streams[MAX_STREAMS_NUMBER];

size_t streams_number;

char buffer[BUFFER_SIZE];

int append;

void check_for_parameters(int argc, const char ** argv) {
    const char * arg;

    for (size_t i = 1; i < argc; i++)
    {
        arg = argv[i];
        if (strcmp(arg, "-a") == 0) {
            append = 1;
        }
    }
}

void add_stream(FILE * stream) {
    streams[streams_number++] = stream;
}

void try_to_open_all_files(int argc, const char ** argv) {
    const char * arg;

    for (size_t i = 1; i < argc; i++)
    {
        arg = argv[i];
        if (arg[0] == '-') continue;
        FILE * stream = fopen(arg, append ? "a" : "w");
        if (stream != NULL) {
            add_stream(stream);
        }
    }   
}

void read_and_write() {
    int c;
    while ((c = fgetc(stdin)) != EOF) {
        for (size_t i = 0; i < streams_number; i++)
        {
            fputc(c, streams[i]);
        }
    }
}

void close_all_but_stdout() {
    for (size_t i = 0; i < streams_number; i++)
    {
        if (streams[i] == stdout) continue;

        fclose(streams[i]);
    }
}

int main(int argc, const char ** argv) {

    check_for_parameters(argc, argv);
    add_stream(stdout);
    try_to_open_all_files(argc, argv);
    read_and_write();
    close_all_but_stdout();
    
    return 0;
}