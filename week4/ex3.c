#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char string[1000]; 
    printf("Write a command or 'exit' to exit : ");
    scanf("%s",string);
    
    //check if command equals exit
	while(strcmp(string, "exit") != 0)  {
		system(string);	
        printf("Write a command or 'exit' to exit : ");
        scanf("%s",string);
	}

	return 0;
}