#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //calculates the average letters per 100 words
    float L = letters / (float)words * 100;
    //calculates the average sentences per 100 words
    float S = sentences / (float)words * 100;
    //calculates the grade level of the passage using the Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    //prints out the grade level based on the value of the index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
//calculates the number of letters by iterating through the passage and checking if the ASCII values are in the range of capital A-Z
int count_letters(string text)
{
    int length = strlen(text);
    int letters = 0;

    for (int i = 0; i < length; i++)
    {
        int value = toupper((int)(text[i])) - 65;
        if (value < 0 || value > 26)
        {
            //adds nothing to the count if one of the characters was not a letter
            letters += 0;
        }
        else
        {
            //adds 1 to the count if the character is a letter
            letters += 1;
        }
    }
    return letters;
}

//calculates the words by seeing how many of the charcters have an ASCII value of 32, which coressponds with a space
int count_words(string text)
{
    int length = strlen(text);
    int words = 1;

    for (int i = 0; i < length; i++)
    {
        int value = text[i];
        if (value == 32)
        {
            //adds 1 to the word count if there is a space
            words += 1;
        }
    }
    return words;
}

//Caculates the number of sentences by looking at how many punctuation symbols there are
int count_sentences(string text)
{
    int length = strlen(text);
    int sentences = 0;

    for (int i = 0; i < length; i++)
    {
        int value = text[i];
        if (value == 33 || value == 46 || value == 63)
        {
            //adds 1 to the word count if there is a space
            sentences += 1;
        }
    }
    return sentences;
}