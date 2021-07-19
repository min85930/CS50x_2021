#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Check arguments is a ValidKey or not
bool IsValidKey(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Caesar’s cipher
string Cipher(string s, int key)
{
    //  Cipher each char with a key
    for (int i = 0, n = strlen(s); i < n ; i++)
    {
        if (isupper(s[i]))
        {
            s[i] = ((s[i] - 'A') + key) % 26 + 'A';
        }
        else if (islower(s[i]))
        {
            s[i] = ((s[i] - 'a') + key) % 26 + 'a';
        }
    }

    return s;
}

int main(int argc, string argv[])
{
    // Check command-line arguments
    if (argc == 2 && IsValidKey(argv[1]))
    {
        // Convert string key to integer
        char *c = argv[1];
        int key = atoi(c);

        string plaintext = get_string("plaintext: ");

        printf("ciphertext: %s\n", Cipher(plaintext, key));
    }
    else
    {
        // if command-line without argument or with more than one, print an error message
        printf("Usage: ./caesar key\n");
        return 1;
    }
}