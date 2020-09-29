#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_realloc(void *ptr, size_t current_size, size_t new_size)
{
    if (ptr == NULL)
    {
        return malloc(new_size);
    }

    if (new_size == 0)
    {
        free(ptr);
        return ptr;
    }

    void *new_ptr = malloc(new_size);

    size_t minimum_size;
    if (current_size > new_size)
        minimum_size = new_size;
    else
        minimum_size = current_size;
    
    memcpy(new_ptr, ptr, minimum_size);

    free(ptr);

    return new_ptr;
}

int main()
{
    int old_size;
    printf("Enter original array size: ");
    scanf("%d", &old_size);

    int *array = malloc(sizeof(int) * old_size);

    for (size_t i = 0; i < old_size; i++)
    {
        array[i] = 100;
    }

    for (size_t i = 0; i < old_size; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");

    int new_size;
    printf("Enter new array size: ");
    scanf("%d", &new_size);

    array = my_realloc(array, old_size * sizeof(int), new_size * sizeof(int));

    for (size_t i = 0; i < new_size; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}