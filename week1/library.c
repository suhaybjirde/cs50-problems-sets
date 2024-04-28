#include <stdio.h>
#include <stdbool.h>


int getInt(char *prompt)
{
    int number;
    char inputBuffer[100];
    bool isValidInput = false;

    while (!isValidInput)
    {
        printf("%s",prompt);
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        
        if (sscanf(inputBuffer, "%d", &number) == 1)
        {
            isValidInput = true;
        } 
        else {
            printf("invalid input please enter an integer!\n");
        } 
    }
    return number;
}