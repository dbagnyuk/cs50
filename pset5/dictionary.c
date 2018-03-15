/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Node Definition
typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;

// Root Node
node* root;

// Size of trie
unsigned int total_nodes = 0;

/**
 * Returns index of letter within trie array
 */
int getIndex(const char c)
{
    if (c == '\'') 
    {
        return 26;    
    }
    else 
    {
        return tolower(c) % 'a';
    }
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    // Set cursor to root
    node* cursor = root;
    
    // for each letter in input word
    for (int i = 0; word[i] != '\0'; i++) 
    {
        // Find the index of the letter
        int index = getIndex(word[i]);
        
        // got to corresponding element in children
        if (cursor->children[index] == NULL) 
        {
            // if NULL word is mispelled
            return false;
        }
        
        // if not NULL, move to next letter
        cursor = cursor->children[index];
    }
    
    // once at end of input word, check if is_word is true
    return cursor->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    // Create space for root
    // problem with malloc is that the malloc is NOT initialised the space
    // which allocated and when the first access to this memory we have next error
    // "Uninitialised value was created by a heap allocation" and
    // "Conditional jump or move depends on uninitialised value(s)"
//    root = malloc(sizeof(node));
    // the calloc allocate the memory and initialised it by 0
    root = (node*)calloc(1, sizeof(node));
    
    // Initialize number of nodes
    total_nodes = 0;
    
    // Read dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    
    // Set cursor to root
    node* cursor = root;
    
    // Read each character in dictionary
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // Check if newline
        if (c == '\n') 
        {
            // mark as word
            cursor->is_word = true;
            
            // Increment number of nodes
            total_nodes++;
            
            // reset cursor to root to traverse trie again
            cursor = root;
        }
        else 
        {
            // Find the index of the letter
            int index = getIndex(c);
            
            // Check if node exists for letter
            if (cursor->children[index] == NULL) 
            {
                // Create new node
//                cursor->children[index] = malloc(sizeof(node));
                cursor->children[index] = (node*)calloc(1, sizeof(node));
            }

            // Move to next node
            cursor = cursor->children[index];
        }
    }
    
    // Close dictionary
    fclose(fp);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return total_nodes;
}

/**
 * Check node children to see if they can be freed
 */
bool free_nodes(node* ptr)
{
    // Go through node's children
    for (int i = 0; i < 27; i++)
    {
        // If child is pointer, recursively check that one as well
        if (ptr->children[i] != NULL) 
        {
            free_nodes(ptr->children[i]);
        }
    }
    
    // If all chilren are null, free node
    free(ptr);

    return true;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    // Start at root
    return free_nodes(root);
}
