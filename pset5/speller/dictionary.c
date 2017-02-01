/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include <stdio.h>

#include <string.h>

#include <strings.h>

#include <stdlib.h>

#include "dictionary.h"

#include "utils.h"

unsigned int dict_size = 0;

bool loaded = false;

char word[46];


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    
    int hv = get_hash_value(word);
    
    return lookup(hv, word);
    
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE* fp = fopen(dictionary, "r");
    
	while (fscanf(fp, "%s", word) != EOF)
	{
	    
	    int hv = get_hash_value(word);
	    
	    insert_at_node(hv, word);
	    
	    dict_size ++;
	    
	}
	loaded = true;
	return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
 
unsigned int size(void)
{
    if(loaded)
    {
        return dict_size;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    return destroy();
}
