#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int n = 0;
    int population = start;
    while (population < end)
    {
        population = population + (population / 3) - (population / 4);
        n++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", n);
}
