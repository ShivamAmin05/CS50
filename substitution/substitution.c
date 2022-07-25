#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char encrpyt(char letter, string key);
bool only_letters(string key);
bool all_letters(string key);

int main(int argc, string argv[])
{
    string key = argv[1];

    //ends the program if the user enters more than one command line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //ends the program if they key does not have 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (((int)key[i] > 64) && ((int)key[i] <= 90))
        {
            //converts the letters in the key to lowercase by adding 32 to the ASCII value
            key[i] += 32;
        }
    }
    if (only_letters(key) == false)
    {
        printf("Key must only contain letters\n");
        return 1;
    }
    if (all_letters(key) == false)
    {
        printf("Key must contain every letter\n");
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    int text_len = strlen(plaintext);
    printf("ciphertext:");
    for (int i = 0; i < text_len; i++)
    {
        if ((plaintext[i] > 96 && plaintext[i] <= 122) || (plaintext[i] > 64 && plaintext[i] <= 90))
        {
            char cipher_letter = encrpyt(plaintext[i], key);
            printf("%c", cipher_letter);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
bool only_letters(string key)
{
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        int value = (int)key[i];
        if (value < 97 || value > 122)
        {
            return false;
        }
    }
    return true;
}

//checks if every letter is in the key by using two for loops to see if there are any duplicate letters
bool all_letters(string key)
{
    int total = 0;
    for (int i = 0, j = 26; i < j; i++)
    {
        for (int k = i + 1; k < j; k++)
        {
            if (key[i] == key[k])
            {
                return false;
            }
        }
    }
    return true;
}

//changes the original text to the encrpyted on by counting up from the starting ASCII value and changing it to the key if it matches the count
char encrpyt(char letter, string key)
{
    int num_letter = (int)letter;
    if (num_letter > 96 && num_letter <= 122)
    {
        for (int i = 97; i <= 122 ; i++)
        {
            if (num_letter == i)
            {

                num_letter = (int)key[i - 97];
                char new_letter = num_letter;
                return new_letter;
            }
        }
    }
    else if (num_letter > 64 && num_letter <= 90)
    {
        for (int i = 65; i <= 90 ; i++)
        {
            if (num_letter == i)
            {
                num_letter = (int)key[i - 65] - 32;
                char new_letter = num_letter;
                return new_letter;
            }
        }
    }
    char new_letter = num_letter;
    return new_letter;
}