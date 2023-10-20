// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Declare variables
unsigned int word_count;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // Hash word to obtain hash value
    hash_value = hash(word);
    for (node *cursor = table[hash_value]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open the dictionary
    FILE *file = fopen(dictionary, "r");

    // Return NULL if file can't be opened
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Declare a variable called word
    char word[LENGTH + 1];

    // Scan the dictionary for strings up to the end of the file (EOF)
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for the new node
        node *n = malloc(sizeof(node));

        // If malloc returns NULL, return false
        if (n == NULL)
        {
            return false;
        }

        // Copy the word into the node
        strcpy(n->word, word);

        // Calculate hash value and store in node
        hash_value = hash(word);

        // Instert node into hash table at calculated index
        n->next = table[hash_value];
        table[hash_value] = n;

        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to the start of the linked list
        node *cursor = table[i];

        // If cursor isn't NULL, free memory
        while (cursor != NULL)
        {
            // Create temp, move cursor to next node, then free up temp
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}

// External Sources: https://stackoverflow.com/questions/1145217/why-should-hash-functions-use-a-prime-number-modulus
// https://stackoverflow.com/questions/11463514/using-loop-to-traverse-through-linked-list