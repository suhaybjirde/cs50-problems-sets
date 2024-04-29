
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "library.h" // Include user-defined library

int checksum(char *creditCardNumber); // Declare checksum function
void validity(char *firstTwo, int length); // Declare validity function

int main(void)
{
    char *creditCardNumber = getString("Credit Card Number: "); // Prompt user for credit card number
    int result = checksum(creditCardNumber); // Calculate checksum
    if (result != 0)
        printf("Please Enter A Valid Credit Card Number\n"); // Print message if credit card number is invalid

    free(creditCardNumber); // Free memory allocated for credit card number
}

int checksum(char *creditCardNumber)
{
    int length = strlen(creditCardNumber); // Calculate length of credit card number
    int sum = 0;
    int i = length - 1;

    int count = 0; // Count for subtracting 9's if doubled number > 9
    if (length > 16 || length < 13) // return immidiataly if the digits are less than 13 or greater than 16
        return 1; // Return error code
    
    if (isOnlyNumbers(creditCardNumber) == 1) // chech the credit card number is only numbers
        return 2;
    while (i >= 0)
    {
        int numbered = creditCardNumber[i] - '0'; // Convert char to integer

        if (i % 2 == 0)
        {
            if (numbered * 2 > 9)
                count++; // Increment count if doubled number > 9
            sum += numbered * 2; // Double every second digit from the right and add together
        } 
        else
        {
            sum += numbered; // Add together every other digit
        }
        i--;
    }
    sum -= count * 9; // Subtract 9's

    char firstTwo[3] = {creditCardNumber[0], creditCardNumber[1], '\0'}; // Extract first two digits

    if (sum % 10 == 0) // Check if checksum is valid
        validity(firstTwo, length); // Check validity of credit card number
    
    return (sum % 10); // Return checksum
} 

void validity(char *firstTwo, int length)
{
    int number = atoi(firstTwo); // Convert first two digits to integer
    bool isMasterCard = false;

    for (int i = 51; i <= 55; i++) // Check for Mastercard range
    {
        if (length == 16 && number == i)
        {
            isMasterCard = true; // Set flag for Mastercard
            break;
        }
    }
    if (isMasterCard)
        printf("MASTERCARD"); // Print if Mastercard
    else if ((length == 15 && number == 34) || (length == 15 && number == 37))
        printf("AMEX"); // Print if American Express
    else if ((length >= 13 && length <= 16) && (firstTwo[0] - '0' == 4))
    {
        printf("VISA"); // Print if Visa
    }
    else 
        printf("INVALID"); // Print if invalid
}
