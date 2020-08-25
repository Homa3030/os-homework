#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i=0 ; i < n ; i++){
        for (int j = n - i - 2; j > -1 ; j--){
            putchar(' ');
        }

        for (int k = 0; k < 1+i*2 ; k++){
            putchar('*');
        }

        putchar('\n');
    }

    return 0;
}