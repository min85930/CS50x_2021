#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Get user input dollars
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    // Convert dollars to integer
    int cents = round(dollars * 100);

    int coins = 0;

    // Calculate minimum number of coins
    while (cents > 0)
    {
        // Greedy Algorithms
        if ((cents - 25) >= 0)
        {
            cents -= 25;
        }
        else if ((cents - 10) >= 0)
        {
            cents -= 10;
        }
        else if ((cents - 5) >= 0)
        {
            cents -= 5;
        }
        else if ((cents - 1) >= 0)
        {
            cents -= 1;
        }

        coins++;
    }

    printf("%i\n", coins);
}