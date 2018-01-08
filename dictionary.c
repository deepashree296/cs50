// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int get_index(char c);
void free_node(dict *node);

// declaring root node for dictionary

dict *root ;
dict *end;
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    dict *traverse = root;
    //dict *end_address = root->children[27];
    // read all characters of word till end of string
    if (word != NULL)
    {
        for ( int i = 0; word[i] != '\0'; i++)
        {
            // get index
            int index = get_index(word[i]);

            if (traverse->children[index] != NULL)
            {
                traverse = traverse->children[index];
            }
            else
            {
                return false;
            }

        }

        if (traverse->children[27] != NULL)
        {
            return true;
        }

    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // open dictionary in read mode
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("error in opening dictionary");
        return 1;
    }

    // allocating space for root node

    root = (dict *)calloc(1, sizeof(dict));

    // allocating space for end character
    end = (dict *)calloc(1, sizeof(dict));



    // read  words from dictionary character by character

    dict *traversal = root;

    for (char c = fgetc(file); c != EOF; c = fgetc(file) )
    {
        // for every word in dictionary file
        if ( c == '\n' )
        {
            // a word is completed
            count++;
            // marking the end of the word in the node
            traversal->children[27] = end;
            // setting traversal pointer to root node before every word is loaded in memory
            traversal = root;
        }
        else
        {
            // get index for the character
            int index = get_index(c);

            if (traversal->children[index] == NULL)
            {
                // malloc a new node and store returned address in the index position of root node
                dict *new_node = calloc(1, sizeof(dict));
                traversal->children[index] = new_node;
                traversal = new_node;
            }
            else
            {
                traversal = traversal->children[index];
            }
        }

    }

    // closing dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // free all children nodes
    free(end);
    free_node(root);
    return true;
}

int get_index(char c)
{
    int index = -1;
    // get the index corresponding to all alphabets and apostrophe
    if (isalpha(c))
    {
        c = tolower(c);
        index = c - 97;
    }
    else if (c == '\'')
    {
        index = 26;
    }

    return index;

}


void free_node(dict *node)
{
    // free all children nodes recursively passing the root node

    for (int i = 0; i < 27; i++)
    {
        if (node->children[i] != NULL)
        {
            free_node(node->children[i]);
        }
    }
    free(node);
}