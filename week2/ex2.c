#include <stdio.h>
#include <string.h>

int main() {
    char string[100];
    scanf("%s", string);

    for (int i = strlen(string) - 1; i > -1 ; i --){
        putchar(string[i]);
    }

    return 0;
}