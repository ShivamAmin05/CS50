#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //asks the user how tall they want the pyramid to be
    int height = get_int("Enter the height of the pyramid(from 1-8): ");
    //if the user puts in an invalid height it asks them to reinput their answer
    while ((height < 1) || (height > 8))
    {
        height = get_int("That is an invalid, height enter another value: ");
    }

    int width = 1;
    int empty = height - width;
    // prints a new line for every row of the pyramid
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < empty; k++)
        {
            // prints empty spaces to the left of the pyramid to make it alligned
            printf(" ");
        }
        for (int j = 0; j < width; j++)
        {
            // prints each collum of the pyramid
            printf("#");
        }
        // used to make the width bigger each row and the empty space smaller each row
        width++;
        empty = height - width;
        printf("\n");
    }
}
