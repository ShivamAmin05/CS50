#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // takes the user name as a string input
    string name = get_string("What is your name? ");
    // prints out the hello then the user's name
    printf("Hello, %s\n", name);
}