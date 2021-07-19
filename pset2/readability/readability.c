#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void count_letters(string text);
void print_grade(float index);

int letter = 0;
int word = 0;
int sentence = 0;

int main(void)
{
    string text = get_string("Text: ");
    count_letters(text);

    // Coleman-Liau index
    float L = (float) letter / word * 100;
    float S = (float) sentence / word * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    print_grade(index);
}

void count_letters(string text)
{

    for (int i = 0, n = strlen(text); i < n ; i++)
    {
        if (isalpha(text[i]))
        {
            // Count letters
            letter++;
        }
        else if (isspace(text[i]))
        {
            // Count words
            word++;
        }
        else
        {
            if ((text[i] == '!') || (text[i] == '?') || (text[i] == '.'))
            {
                // Count sentences
                sentence++;
            }
        }
    }

    if (word > 0)
    {
        word++;
    }
}

void print_grade(float index)
{
    if (round(index) < 1)
    {
        // Grade less than 1
        printf("Before Grade 1\n");
    }
    else if (round(index) >= 16)
    {
        // Grade equal or greater than 16
        printf("Grade 16+\n");
    }
    else
    {
        // Print Grade
        printf("Grade %.0f\n", round(index));
    }
}