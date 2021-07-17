#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get user input height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    // Print mario bricks
    for (int i = 0; i < height; i++)
    {
        // Print space and #
        for (int j = 0; j < (height - (i + 1)); j++)
        {
            printf(" ");
        }
        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }
        printf("  ");
        // Print opposite #
        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }
        printf("\n");
    }
}