// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 65366;

// Hash table
node *table[N];
int number_of_words=0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int word_ind=hash(word);
    node *cursor=table[word_ind];
    while (cursor!=NULL)
    {
        if (strcasecmp(cursor->word,word)==0)
        {
            return true;
        }
        cursor=cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_val = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        char lowercase_char = tolower(word[i]);
        hash_val = hash_val * 31 + lowercase_char;
    }
    return hash_val % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict=fopen(dictionary,"r");
    if (dict==NULL)
    {
        printf("Couldn't open a dictionary");
        return false;
    }
    char word[LENGTH+1];
    while (fscanf(dict,"%s",word)!=EOF)
    {
        node *new_node=malloc(sizeof(node));
        if (new_node==NULL)
        {
            fclose(dict);
            printf("Memory allocation failed");
            return false;
        }
        strcpy(new_node->word,word);
        unsigned int ind=hash(word);
        new_node->next=table[ind];
        table[ind]=new_node;
        number_of_words+=1;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i=0;i<N;i++)
    {
        node *cursor=table[i];
        while (cursor!=NULL)
        {
            node *tmp=cursor;
            cursor=cursor->next;
            free(tmp);
        }
    }
    return true;
}
