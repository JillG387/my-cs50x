#include <stdio.h>
#include <cs50.h>

//Say hello to a person
int main(void)
{
    string name = get_string("What is your name? ");
    printf("hello, %s\n", name);
}