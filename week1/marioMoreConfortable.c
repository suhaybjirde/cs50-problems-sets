#include <stdio.h>
#include <stdbool.h>

#include "library.h"

int main(void)
{
    int number = getInt("input: ");

    while ( number < 0 || number > 8)
    {
        printf("number is less than 8 and greater than 0!\n");
        number = getInt("input: ");
    }

    for (int i = number; i > 0; i--)
    {
        for (int j = 0; j <= (2 * number) + 2; j++)
        {
            if (j > number && j <= number + 2)
                printf(" ");
            else if (j < i && j < number)
                printf(" ");
            else if (j > (number * 2 + 3) - i)
                printf(" ");
            else
                printf("#");
        }
        printf("\n");
    }
}
