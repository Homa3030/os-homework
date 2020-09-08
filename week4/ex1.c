#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{
    int pid = fork(); 
    int n = 10;
    if (pid == 0)
        printf("Hello from child [%d - %d] \n", getpid(), n);
    else
    {
        if (pid > 0)
            printf("Hello from parent [%d - %d] \n", getpid(), n);
        else
            return EXIT_FAILURE;
    }
    

    // PIDs are different every time you run this code.
    // However, child's PID is always equal to its parent's PID + 1.
    // This happens due to the fact that there is a new proccess
    // gets created whenever program is run. Thus, PIDs are not the same.
    // Also, there is a chance of OS running some other processes between
    // moments when you run them. Again, PIDs become slightly different.

    return 0; 
} 