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
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    node *cursor = table[hash_value];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        //adds together the ASCII value of all the letters in the word
        total = (int)(toupper(word[i]));
    }
    //subtracts 65 times the number of letters so that the first bucket is 0(if the word is a or aaaa)
    total -= (strlen(word) * 65);
    // total is moduloed by N so that when total becomes greater than N, the value is reset to 0
    total = total % N;
    return total;
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }
        //copies entire array
        strcpy(n->word, word);
        int hash_value = hash(word);
        //sets the pointer of the new node to the head of the original linked list
        n->next = table[hash_value];
        //sets the original head of the linked linked list to be the new node
        //this sets the first value of the linked list to be the new node
        table[hash_value] = n;
        dict_size++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        //sets the cursor to the first value in the linked list
        node *cursor = table[i];
        while( cursor != NULL)
        {
            //sets a temp node equal to the cursor
            node *tmp = cursor;
            cursor = cursor->next;
            //moves the cursor forward and then frees the tmp value so the pointers to the next values are not lost, this continues until the cursor points to NULL
            free(tmp);
        }
        free(cursor);
    }
    return true;
}