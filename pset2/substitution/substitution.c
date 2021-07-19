#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Check arguments is a ValidKey or not
bool CheckValid(string s)
{
    int n = strlen(s);

    // check key length
    if (n != 26)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        // check invalid characters in key
        if (!isalpha(s[i]))
        {
            return false;
        }

        // check duplicate characters in key
        for (int j = 0; j < i; j++)
        {
            if (s[i] == s[j])
            {
                return false;
            }
        }
    }

    return true;
}

// substitution cipher
string Cipher(string s, string key)
{
    //  Cipher each char with a key
    for (int i = 0, n = strlen(s); i < n ; i++)
    {
        // check char isupper or islower
        if (isupper(s[i]))
        {
            s[i] = toupper(key[(s[i] - 'A') % 26]);
        }
        else if (islower(s[i]))
        {
            s[i] = tolower(key[(s[i] - 'a') % 26]);
        }
    }

    return s;
}

int main(int argc, string argv[])
{
    // Check command-line arguments
    if (argc == 2)
    {
        string key = argv[1];

        if (!CheckValid(key))
        {
            return 1;
        }

        string plaintext = get_string("plaintext: ");

        printf("ciphertext: %s\n", Cipher(plaintext, key));
    }
    else
    {
        // if command-line without argument or with more than one, print an error message
        printf("Usage: ./substitution key\n");
        return 1;
    }
}