/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include <stdio.h>

#include <string.h>

#include <strings.h>

#include <stdlib.h>

#include "dictionary.h"

unsigned int dict_size = 0;

bool loaded = false;

char word[46];

typedef struct node
{
    char val[46];
    struct node* next;
} node_t;

node_t* head;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    
    node_t* crawler = head;
    
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

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE* fp = fopen(dictionary, "r");
    
	while (fscanf(fp, "%s", word) != EOF)
	{
	    
	    node_t* inode = malloc(sizeof(node_t));
	    if(inode==NULL)
	    {
	        return false;
	    }
	    strcpy(inode->val, word);
	    
	    if(!head)
	    {
	        
	        head = inode;
	        head->next = NULL;
	        
	    }
	    else
	    {
	        
	        node_t* dhead = head;
	        inode->next = dhead;
	        head = inode;
	    }
	    
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
    
    while(head != NULL)
    {
        node_t* next_head = head->next;
        free(head);
        head = next_head;
    }
    return true;
}
