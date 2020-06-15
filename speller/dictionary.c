// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// Number of buckets in hash table (first try: create buckets for words starting with each character and having length of 1 to 45)
const unsigned int N = 26 * 45;

//counter of words in dictionary
int total_words = 0;

// Hash table
node* table[N];

// Returns true if word is in dictionary else false
bool check(const char* word)
{
    //convert the word from checked text to lowercase.
    char word_lower[LENGTH + 1];

    strcpy(word_lower, word);

    for (int i = 0; i < strlen(word_lower); i++)
    {
        word_lower[i] = tolower(word_lower[i]);
    }

    //find the bucket to which this word belongs
    int bucket = (strlen(word_lower) - 1) * 26 + word_lower[0] - 97;

    for (node* n = table[bucket]; n != NULL; n = n->next)
    {
        if (strcmp(n->word, word_lower) == 0)
        {
            return true;
        }
    }

    return false;
}


// Hashes word to a number
unsigned int hash(const char* word)
{
    //all buckets were indexed by number of characters in a word and then by alphabetical order (first letter)
    int bucket = (strlen(word) - 1) * 26 + word[0] - 97;

    return bucket;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char* dictionary)
{
    FILE* dict = fopen(dictionary, "r");
    char dict_word[LENGTH + 1];

    if (dict == NULL)
    {
        return false;
    }

    //clear table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //read each word in dictionary and put all words into corresponding buckets
    while (fscanf(dict, "%s", dict_word) == 1)
    {
        node* single_node = malloc(sizeof(node));

        if (single_node == NULL)
        {
            return false;
        }

        int bucket = hash(dict_word);

        strcpy(single_node -> word, dict_word);
        single_node -> next = table[bucket];

        table[bucket] = single_node;

        total_words += 1;
    }

    fclose(dict);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (total_words == 0)
    {
        return 0;
    }

    return total_words;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int nodes_freed = 0;

    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node* tmp = table[i];

            table[i] = table[i]->next;

            free(tmp);
            nodes_freed += 1;
        }
    }

    if (nodes_freed == total_words)
    {
        return true;
    }

    return false;
}