#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string key);
char rotate(char letter, int key);

int main(int argc, string argv[])
{
    //ends the program if the user enters more than one command line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // ends the function if the command line argument contains a character that is not a number
    if (!(only_digits(argv[1])))
    {
        return 1;
    }
    //converts the command line argument into an int
    int shift_num = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    int text_len = strlen(plaintext);
    printf("ciphertext:");
    for (int i = 0; i < text_len; i++)
    {
        //shifts the character by the key if it is a uppercase or lowercase letter
        if ((plaintext[i] > 96 && plaintext[i] < 123) || (plaintext[i] > 64 && plaintext[i] < 91))
        {
            char cipher_letter = rotate(plaintext[i], shift_num);
            printf("%c", cipher_letter);
        }
        else
        {
            //prints the orginal character if it not a letter
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

//checks if the charcter is a int from 0-9
bool only_digits(string key)
{
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        int value = (int)key[i];
        if (value < 48 || value > 57)
        {
            printf("Usage: ./caesar key\n");
            return false;
        }
    }
    return true;
}
//shifts the letter by taking the ASCII value of the letter adding it to the key, then uses modulo to find the remainder between the new letter and the first position. Repeats the funtion until the letter is in a valid range which is 1-25 more than the starting letter
char rotate(char letter, int key)
{
    int num_letter = (int)letter + key;
    while (num_letter > 26)
    {
        if ((int)letter > 96 && (int)letter < 123)
        {
            num_letter = (num_letter % 96);
            if (num_letter > 26)
            {
                num_letter -= 26;
            }
        }
        if ((int)letter > 64 && (int)letter < 91)
        {
            num_letter = (num_letter % 64);
            if (num_letter > 26)
            {
                num_letter -= 26;
            }
        }
    }
    //adds the difference from the starting position to the postition of the first letter
    if ((int)letter > 64 && (int)letter < 91)
    {
        num_letter += 64;
    }
    if ((int)letter > 96 && (int)letter < 123)
    {
        num_letter += 96;
    }
    char new_letter = num_letter;
    return new_letter;
}