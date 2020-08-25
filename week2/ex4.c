#include <stdio.h>

void swap(int* first_number, int* second_number){
    int temp;
    temp = *first_number;
    *first_number = *second_number;
    *second_number = temp;
}

int main(){
    int first_number;
    scanf("%d", &first_number);

    int second_number;
    scanf("%d", &second_number);

    swap(&first_number, &second_number);
    printf("First number = %d\n", first_number);
    printf("Second number = %d\n", second_number);
}