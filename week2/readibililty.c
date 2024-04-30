#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "library.h"

void checkColemanIndex(int sentences, int words, int letters);
void calculate_grade(char* story);
int count_sentences(char *story);
int count_words(char *story);
int count_letters(char *story);
float compute_average_letters_per_100_words(int letters, int words);
float compute_average_sentences_per_100_words(int sentences, int words);
int calculate_coleman_liau_index(float L, float S);
void get_grade_level(int index);

int main()
{
    char *story = getString("enter sentence: ");

    int sentences = count_sentences(story);
    int words = count_words(story);
    int letters = count_letters(story);
    
    float L = compute_average_letters_per_100_words(letters, words);
    float S = compute_average_sentences_per_100_words(sentences, words);
    
    int index = calculate_coleman_liau_index(L, S);
    
    get_grade_level(index);

    free(story);
}

void checkColemanIndex(int sentences, int words, int letters)
{

    float L = ((float)sentences / words) * 100;
    float S = ((float)letters / words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 0)
        printf("before grade 1\n");
    else if (index >= 16)
        printf("grade 16+\n");
    else 
        printf("grade %d\n", round(index));
}

int count_sentences(char *story)
{
    int sentences = 0;
    int counter = 0;
    while (story[counter] != '\0')
    {
        if(story[counter] == '.' || story[counter] == '!' || story[counter] == '?')
        {
            sentences++;
        }
        counter++;
    }
    return sentences;
}

int count_words(char *story)
{
    int words = 0;
    int counter = 0;
    while (story[counter] != '\0')
    {
        if (isspace(story[counter]))
            words++;
        counter++;
    }
    if (story)
        words++;
    return words;
}
int count_letters(char *story)
{
    int letters = 0;
    int counter = 0;
    while (story[counter] != '\0')
    {
        if (islower(story[counter]) || isupper(story[counter]))
        {
            letters++;
        }
        counter++;
    }
    return letters;
}

float compute_average_letters_per_100_words(int letters, int words) {
    return ((float) letters / words) * 100;
}

float compute_average_sentences_per_100_words(int sentences, int words) {
    return ((float) sentences / words) * 100;
}

int calculate_coleman_liau_index(float L, float S) {
    return 0.0588 * L - 0.296 * S - 15.8;
}

void get_grade_level(int index) {
    if (index < 1) {
        printf("Before Grade 1");
    } else if (index >= 16) {
        printf("Grade 16+");
    } else {
        printf("Grade: %i", index);
    }
}