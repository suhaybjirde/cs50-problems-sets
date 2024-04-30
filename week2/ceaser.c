#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"

char encipher(char letter, int key);
void print_cipheredText(char* text, int key);

int main(int argc, char* argv[])
{
    int key = atoi(argv[1]);

    if (argc != 2 || key < 0 || key >= 26)
    {
        printf("usage: ./filename key<number between 0 and 26>");
        return 1;
    }

    char *text = getString("Enter Text: ");
    print_cipheredText(text, key);
    

}
void print_cipheredText(char* text, int key) {
    char ciphered_text[1000] = "";

    int counter = 0; 
    while (text[counter] != '\0')
    {
        ciphered_text[counter] = encipher(text[counter], key);
        counter++;
    }
    ciphered_text[strlen(ciphered_text)] = '\0';
    printf("%s\n", ciphered_text);
}
char encipher(char letter, int key)
{
    char ciphered;
    if (isdigit(letter) || ispunct(letter) || isspace(letter))
    {
        ciphered = letter;
    } 
    else if (islower(letter))
    {
        if (letter + key > 'z')
            ciphered = ('z' - 26) + key;
        else
            ciphered = letter + key;
    }
    else if (isupper(letter))
    {
        if (letter + key > 'Z')
            ciphered = 'A' + ((letter + key) - 'Z');
        else
            ciphered = letter + key;
    }
    return ciphered;
}

