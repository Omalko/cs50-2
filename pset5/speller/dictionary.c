/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include <stdio.h>

#include "dictionary.h"

FILE *fp;
char word[45];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    fp = fopen(dictionary, "r");
    
	while (fscanf(fp, "%s", word) != EOF)
	{
		printf("Dictionary word is: %s\n", word);
	}
	return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
 
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
