#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


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

char* getString(char *prompt)
{
    int bufferSize = 20; // asuming the credit card number is less than 19 digits

    char *buffer = malloc(bufferSize * sizeof(char));

    if (buffer == NULL)
    {
        printf("could allocate memory");
        return NULL;
    }
    printf("%s", prompt);
    fgets(buffer, bufferSize, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    return buffer; // you should also free when you use this buffer
}