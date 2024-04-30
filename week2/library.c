#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* getString(char *prompt)
{
    int bufferSize = 50;

    char *buffer = malloc(bufferSize * sizeof(char));

    if (buffer == NULL)
    {
        printf("could allocate memory");
        return NULL;
    }
    printf("%s", prompt);
    fgets(buffer, bufferSize, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    return buffer; // you should also free when you use this buffer to avode memory leak
}
