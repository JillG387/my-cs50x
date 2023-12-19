#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])

// Run program with one command-line argument, otherwise print the error message
{
    if (argc != 2)
    {
        printf("Useage: ./caesar Key\n");
        return 1;
    }

// Define the key
    string key = argv[1];

// Loop looking at the text. If it's not a digit, print the error message
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar Key\n");
            return 1;
        }
    }
// Ask user for the plaintext
    string plaintext = get_string("Plaintext: ");

// Convert they key (a string) into an integer so we can use math with it
    int k = atoi(key);
    printf("Ciphertext: ");

// Make a loop and convert plaintext to cyphertext. When a letter hits Z or z, it loops back to A (or 0) or a (or 97)
    for (int t = 0; t < strlen(plaintext); t++)
    {
        if (isupper(plaintext[t]))
        {
            printf("%c", (((plaintext[t] - 65) + k) % 26) + 65);
        }

        else if (islower(plaintext[t]))
        {
            printf("%c", (((plaintext[t] - 97) + k) % 26) + 97);
        }

// Telling it to keep everything else, i.e., numbers or punctuation, the way they are
        else
        {
            printf("%c", plaintext[t]);
        }
    }
    printf("\n");
}
