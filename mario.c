#include <cs50.h>
#include <stdio.h>

int main(void)

//Prompt for height
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

//The pyramid hash pattern
    for (int i = 0; i < n; i++)
    {

//The spaces in the pyramid
        for (int j = 1; j < n - i; j++)
        {
            printf(" ");
        }

//The left hashtag pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}