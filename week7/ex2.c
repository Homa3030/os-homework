#include <stdio.h>
#include <stdlib.h>

void fill_array(int *array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array[i] = i;
    }
}

void print_array(int *array, size_t size)
{
    printf("Array: ");

    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int main()
{
    size_t n;

    printf("Enter the size of the array: ");
    scanf("%lu", &n);

    int *array = (int *) calloc(n, sizeof(int));

    fill_array(array, n);
    print_array(array, n);

    free(array);

    return 0;
}