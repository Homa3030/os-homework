#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{
    for(int i = 0; i < 5; i++){
        fork();
    }

    sleep(5);

    /*
        Before loop: 1
        After 1'st iteration: 2
        After 2'nd iteration: 4
        After 3'rd iteration: 8
        The number doubles at each iteration because each of existing processes creates a clone of itself.
    */
    
    return 0;
}