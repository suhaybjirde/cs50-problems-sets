#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int votes;
}
candidate;

int get_voters(void);
char *get_votes(void);
void print_votes(candidate candidates[], int len);


int main(int argc, char *argv[])
{
    int length = argc - 1;
    candidate candidates[length];
    for (int i = 0; i <= length; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }
    int voters = get_voters();
    while (voters > 0)
    {
        char *candidate_name = get_votes();
        for (int i = 0; i < length; i++)
        {
            if (strcmp(candidates[i].name, candidate_name) == 0)
                {
                    candidates[i].votes++;
                }
        }
        voters--;
        free(candidate_name);
    }
    print_votes(candidates, length);
    
}

int get_voters(void)
{   
    int voters;
    printf("how many voters: ");
    scanf("%d", &voters);
    return voters;
}

char *get_votes(void)
{
    char *candidate_name = (char *)malloc(50 * sizeof(char));
    printf("vote: ");
    scanf("%s", candidate_name);
    return candidate_name;
}

void print_votes(candidate candidates[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("name: %s, votes: %i\n", candidates[i].name, candidates[i].votes);
    }
}