// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;
unsigned int count_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int backet = hash(word);

    node *cursor = table[backet];
    while (cursor != NULL) 
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashValue = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (i == 1)
        {
            hashValue += (tolower(word[i] - 'a'));
            break;
        }    
            
        hashValue += (tolower(word[i]) - 'a') * 26;
    }
    return hashValue;
    
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("couldn't open the dictionary file!\n");
        return false;
    }

    char str[LENGTH + 1];
    while (fscanf(file, "%s", str) != EOF)
    {
        node *temp = malloc(sizeof(node));
        strcpy(temp->word, str);

        unsigned int backet = hash(temp->word);

        temp->next = table[backet];
        table[backet] = temp;
        count_words++;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
