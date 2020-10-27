#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STRING "Hello"

char buffer[256];

int main() {
    setvbuf(stdout, buffer, _IOLBF, 256);

    size_t string_length = strlen(STRING);

    for (size_t i = 0; i < string_length; i++)
    {
        printf("%c", STRING[i]);
        sleep(1);
    }
    

    return 0;
}