#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    for (size_t i = 0; i < 10 ; i++)
    {
        void * data = malloc(10485760);
        memset(data, 0, 10485760);
        sleep(1);
    }

    // the further program goes, the more so is (pages are getting swapped out)

    return 0;
}