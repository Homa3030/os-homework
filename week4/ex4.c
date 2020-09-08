#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char string[1000];

int processMyBg(char ** argv, char ** envp) {
    // check if stats with "mybg"
    if (strstr(string, "mybg") != string) return 0;

    // lenngth of "mybg"
    int myBgCmdLen = strlen("mybg");
    // extract file name (assuming a single space character)
    char * fileName = string + myBgCmdLen + 1;

    // fork to create a background process.
    if (fork() == 0) {
        printf("Starting background process...\n");
        execve(fileName, argv, envp);
        exit(0);
    }


    return 1;
}

int main(int argc, char ** argv, char ** envp) {

    while (1) {
        printf("Write a command or 'exit' to exit : ");
        // read command
        fgets(string, 1000, stdin);
        
        //check if command equals exit
        if (strcmp(string, "exit\n") == 0) {
            return 0;
        }
        else if (processMyBg(argv, envp)) {
            // mybg [file_name] runs program in background
            // check if starts with "mybg"
        }
        else {
            system(string);
        }
    }

    return 0;
}