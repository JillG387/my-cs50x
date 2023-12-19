#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


int main(void)

// Ask user for some text
{
    string text = get_string("Text: ");

    int letters = 0;
    int words = 1;
    int sentences = 0;

// Count letters, spaces between words, and sentences using punctuation
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }

        else if (text[i] == ' ')
        {
            words++;
        }

        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

// Use the Coleman-Liau index of a text to determine U.S. grade level of the text
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

// If the index number is less than 1
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

// If the index number is greater than 16
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }

// Otherwise print the grade level
    else
    {
        printf("Grade %i\n", index);
    }
}
