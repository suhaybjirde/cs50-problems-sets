#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "library.h"

// function prototypes
int hashFunction(char letter);

int sum(char *string);

int main(void)
{
    // get the word from both the players 
    char* player1 = getString("Player 1: ");
    char* player2 = getString("Player 2: ");
    // get the points of the players
    int player1Points = sum(player1);
    int player2Points = sum(player2);
    // check who wins
    if (player1Points > player2Points)
        printf("player1 Win: %i points \n", player1Points);
    else if (player2Points > player1Points)
        printf("player2 Win: %i points\n", player2);
    else
        printf("Tie!\nplayer1: %i, player2: %i points\n", player1Points, player2Points);
    // free the momery we allocated to store the string from the stdin; getstring also tells us to free after we finish with it
    free(player1);
    free(player2);
}
// map every letter by corresponding point
int hashFunction(char letter) {
    int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    if ((toupper(letter) - 65) >= 0 && (toupper(letter) - 65) < 26)
        return POINTS[toupper(letter) - 'A'];
    return 0;
}
// sum the points of each letter in a string 
int sum(char *string)
{
    int sum = 0;
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        sum += hashFunction(string[i]);
    }
    return sum;
}