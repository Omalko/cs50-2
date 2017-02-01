/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include <stdio.h>

#include <string.h>

#include <strings.h>

#include <stdlib.h>

#include <ctype.h>

#include "dictionary.h"

unsigned int dict_size = 0;

bool loaded = false;

char word[46];

typedef struct node
{
    char val[46];
    struct node* next;
} node_t;

node_t* hash_dict[2048];

int get_hash_value(const char *word)
{
    
    int asum = 0;
    
	for(int i=0; i<strlen(word); i++)
	{
	    
		char lc = tolower(word[i]);
		
		asum += (int) lc;
	}
	
	return asum % 2048;
}

void insert_at_node(int dict_index, const char* word)
{
    
    node_t* inode = malloc(sizeof(node_t));
    strcpy(inode->val, word);
    inode->next = NULL;
    
	// check to see if there is anything at the dictionary pointer
	if (!hash_dict[dict_index])
	{
		hash_dict[dict_index] = inode;
	}
	// here we know the list is not empty
	else
	{
		node_t* old_head = hash_dict[dict_index]; // create oldhead to hold old head
		inode->next = old_head;
		hash_dict[dict_index] = inode;
	}
}


bool lookup(int dict_index, const char* word)
{
	
	if (hash_dict[dict_index] == NULL)
	{
		return false;
	}
	else
	{
		node_t* crawler = hash_dict[dict_index];
		while(crawler != NULL)
		{
			if(strcasecmp(crawler->val, word)==0)
			{
				return true;
			}
			crawler = crawler->next;
		}
		return false;
	}
}

bool destroy()
{
	for(int i=0; i<2048; i++)
	{
		if(hash_dict[i])
		{
			node_t* head = hash_dict[i];
			while(head != NULL)
			{
				node_t* new_head = head->next;
				free(head);
				head = new_head;
			}
			
		}
	}
	return true;
}


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
