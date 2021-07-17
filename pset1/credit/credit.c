#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Get user input number
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    int index = 0;
    int checksum = 0;
    long tmp = number;

    // calculate checksum
    while (index < 16)
    {
        int digit = number % 10;
        number /= 10;
        index++;
        // sum digit use Luhn’s Algorithm
        if (index % 2 == 1)
        {
            checksum += digit;
        }
        else
        {
            checksum += (digit * 2) / 10;
            checksum += (digit * 2) % 10;
        }
        // end of length breakout
        if (number == 0)
        {
            break;
        }
    };

    // check for card length and starting digits
    if (checksum % 10 == 0)
    {
        int start = (int)floor(tmp / pow(10, index - 2));

        // print type of card
        if (index == 15 && (start == 34 || start == 37))
        {
            printf("AMEX\n");
        }
        else if (index == 16 && (start >= 51 && start <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((index == 13 || index == 16) && (start / 10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        };
    }
    else
    {
        // print INVALID number
        printf("INVALID\n");
    }
}