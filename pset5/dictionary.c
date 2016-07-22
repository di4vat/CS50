/****************************************************************************
 * dictionary.c
 * 
 * by Divine Attipoe
 * divineattipoe@gmail.com
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// hashtable size large enough to handle collision(25% large)
#define HASHTABLE_SIZE 178864

// node of linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// a hashtable of node of linked list
node* hashtable[HASHTABLE_SIZE];

// counter for size of dictionary
int count = 0; 
// key for dictionary lookup
char key[LENGTH + 1];

/* 
  hash functions from https://study.cs50.net/hashtables 
  works but slow checking time.
  
  int hash_function(char* key)
{
    int hash = toupper(key[0] - 'A');
    return hash %HASHTABLE_SIZE;
}
*/

// hash function(from https://github.com this function speeds up checking time)
unsigned int hash(const char *word)
{
    // start hash at the prime number 5381
    unsigned long hash = 5381;
    int count;

    // iterate through each letter of the word
    while ((count = *word++))
        // bitwise left shift 5, add hash, add count
        hash = ((hash << 5) + hash) + count;

    // make sure our hash is in the array
    return hash % HASHTABLE_SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // convert key to lowercase
    for (int i = 0, n = strlen(word) + 1; i < n; i++)
    {
        if (isupper(word[i]))
            key[i] = tolower(word[i]);
        else
            key[i] = word[i];
    }
    
    int index = hash(key);
    
    // node to traverse hashtable thus the list of words
    node* checker = hashtable[index];
    
    // compares word to key (strcasecmp)
    while (checker != NULL)
    {
        if (strcasecmp(checker->word, key) == 0)
        {
            // if word is the same as key
            return true;
         }
        else
        {
            // checker is next word in dictionary
            checker = checker->next;
        }
    }
    
    // if word not found in dictionary
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */ 
bool load(const char* dictionary)
{    
    // open dictionary
    FILE* fp = fopen(dictionary, "r");

    // check for an unsuccessful open
    if (fp == NULL)
    {
        printf("Could not load %s.\n", dictionary);
        return false;
    }
    
    // load dictionary into hash table
    while (true)
    {
        // create memory location for node
        node* nodes = malloc(sizeof(node));
        if (nodes == NULL)
        {
            printf("Could not create node! Not enough heap memory available");
            return false;
        }
        
        // loops through the file until end of file is reached
        if (fscanf(fp, "%s", nodes->word) == EOF)
        {
            free(nodes);
            break;
        }
        
        // put word into hash table
        else
        {
            // hash word
            int index = hash(nodes->word);
            
            // copy words to hashtable
            nodes->next = hashtable[index];
            hashtable[index] = nodes;

            // count words in dictionary
            count++;
        }
    }
    // close dictionary file
    fclose(fp);
    return true;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // for each table
    for (int i = 0;i < HASHTABLE_SIZE; i++)
    {
        if (hashtable[i] == NULL)
            continue;
            
        node *cursor = hashtable[i];
        
        while (cursor != NULL)
        {
            node *n = cursor;
            cursor = cursor->next;
            free(n);
        }
    }
    
    return true;
}