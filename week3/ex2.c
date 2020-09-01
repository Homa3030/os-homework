#include <stdio.h> 
#include <stdlib.h>
  
//swapping elements
void swap(int *first, int *second) 
{ 
    int temp = *first; 
    *first = *second; 
    *second = temp; 
} 
  
//bubble sort implementation
void bubbleSort(int array[], int size) 
{
   for (int i = 0; i < size-1; i++)
   {
       for (int j = 0; j < size-i-1; j++)
       {
           if (array[j] > array[j+1]) 
              swap(&array[j], &array[j+1]); 
       }
   }
} 


int main() 
{   
    //reading array and the size
    int size;
    scanf("%d", &size);
    int *array = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++){
        scanf("%d", &array[i]);
    }

    bubbleSort(array, size); 

    //printing sorted array
    printf("Sorted array: "); 
    for (int i=0; i < size; i++) 
        printf("%d ", array[i]); 
    printf("\n");  

    return 0; 
} 