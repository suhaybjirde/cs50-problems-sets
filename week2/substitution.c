#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "library.h"
int hash_charactor(char letter);
bool charctar_occurance(char *string);
bool isValid_key(char *key);
bool is_repeated(char *string);
char* encrypt_text(char *plainText, char* key);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("USAGE: ./substitution KEY");
        return 1;
    }

    char* key = argv[1];

    if (!isValid_key(key))
    {
        printf("Ivalid key!");
        return 1;
    }

    char* plain_text = getString("plain text: ");
    char* encrypted_text = encrypt_text(plain_text, key);

    printf("%s\n", encrypted_text);

    free(plain_text);
    free(encrypted_text);
}

bool isValid_key(char *key)
{
    if (strlen(key) != 26)
    {
        printf("key should be equel to 26 charactors!\n");
        return false;
    }
    if (!isAphabeticOnly(key))
    {
        printf("key should contain only Alphabetic charactors!\n");
        return false;
    }
    if (is_repeated(key))
    {
        printf("key shouldn't contain repeated charactors!\n");
        return false;
    }
    return true;
}

bool is_repeated(char *string)
{
    int alphabel_letters[26] = {0};

    for (int i = 0, length = strlen(string); i < length; i++)
    {
        int index = hash_charactor(string[i]);
        alphabel_letters[index]++; 
    }

    for (int i = 0; i < 26; i++)
        if (alphabel_letters[i] > 1)
            return true;
    return false;
}   
int hash_charactor(char letter)
{
    if (letter >= 'a' && letter <= 'z')
        return letter - 'a';
    if (letter >= 'A' && letter <= 'Z')
        return letter - 'A';
}

char* encrypt_text(char *plainText, char* key)
{
    int length = strlen(plainText);
    char* encrypted = malloc((length + 1) * sizeof(char));

    for (int i = 0; i < length; i++) {
        char c = plainText[i];
        if (isalpha(c)) {
            int index = (isupper(c)) ? c - 'A' : c - 'a';
            char encrypted_char = (isupper(c)) ? toupper(key[index]) : tolower(key[index]);

            encrypted[i] = encrypted_char;
        } else {
            encrypted[i] = c;
        }
    }
    encrypted[length + 1] = '\0';
    return encrypted;
}