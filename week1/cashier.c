#include <stdio.h>
#include <stdlib.h>

#include "library.h" // Including header file for additional functions. 

#define QUARTER  25
#define DIME  10
#define NICKEL  5 
#define PENNY  1

int calculate_coins(int cents, int coin_value); // Function prototype for calculating the number of coins of a specific denomination.
void calculate_totalCoins(int cents); // Function prototype for calculating total number of coins needed.

int main(void)
{
    int changeOwed = getInt("change owed: "); // Prompting user to input change owed.
    if(changeOwed < 0)
    {
       printf("change owed must be greater than 0"); // Providing feedback if input is invalid.
       return 1; 
    }    
    calculate_totalCoins(changeOwed); // Calling function to calculate total coins needed.
}

int calculate_coins(int cents, int coin_value)
{
    int total_coin = 0;
    while (cents >= coin_value)
    {
        total_coin++;
        cents = cents - coin_value; // Subtracting coin value from remaining cents.
    }
    return total_coin;
}

void calculate_totalCoins(int cents)
{
    int quarters = calculate_coins(cents, QUARTER); // Calculating number of quarters needed.
    cents = cents - quarters * QUARTER; // Updating remaining cents after considering quarters.
    int dimes = calculate_coins(cents, DIME); // Calculating number of dimes needed.
    cents = cents - dimes * DIME; // Updating remaining cents after considering dimes.
    int nickels = calculate_coins(cents, NICKEL); // Calculating number of nickels needed.
    cents = cents - nickels * NICKEL; // Updating remaining cents after considering nickels.
    int pennies = calculate_coins(cents, PENNY); // Calculating number of pennies needed.
    cents = cents - pennies * PENNY; // Updating remaining cents after considering pennies.
    int total = quarters + dimes + nickels + pennies; // Calculating total number of coins.
    printf("quarters: %i\ndimes: %i\nnickels: %i\npennies: %i\ntotal coins: %i", quarters, dimes, nickels, pennies, total); // Printing the results.
}
