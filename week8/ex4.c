#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>

int main() {

    printf("Memory usage:\n");
    for (size_t i = 0; i < 10; i++)
    {
        void * data = malloc(10485760);
        memset(data, 0, 10485760);

        struct rusage rusage;
        getrusage(RUSAGE_SELF, &rusage);

        printf("%ld sec: ", i+1);
        printf("%ld\n",rusage.ru_maxrss);

        sleep(1);
    }

    return 0;
}