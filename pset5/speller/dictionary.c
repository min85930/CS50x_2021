// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Numbers of word in load dictionary
int words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *list = table[hash(word)];

    while (list != NULL)
    {
        node *tmp = list->next;

        if (!strcasecmp(list->word, word))
        {
            return true;
        }

        list = tmp;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int code = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        code += tolower(word[i]);
    }

    return code % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(inptr, "%s\n", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);

        int code = hash(word);
        if (table[code] == NULL)
        {
            table[code] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[code];
            table[code] = n;
        }

        words++;
    }

    fclose(inptr);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];

        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return true;
}
