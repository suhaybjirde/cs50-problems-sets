#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* get_string(char* prompt, int rank)
{
    char buffer[100];
    printf(prompt, rank);
    scanf("%s", buffer);
    return strdup(buffer);
}


int get_int(char* prompt)
{
    int input;
    printf("%s", prompt);
    scanf("%d", &input);
    return input;
}