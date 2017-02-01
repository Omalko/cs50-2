#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>

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