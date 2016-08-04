/*
counters.c          Daniel Moder        July 2016
This file contains the definitions of a counters struct. It includes functions:
    counters_new
    counters_add
    counters_get
    counters_delete
    
and helper functions:
    countersNode_new
    nodeSearch
*/

#include "counters.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct countersNode
{
	struct countersNode* next;
	int key;
	int count;
}countersNode_t;

typedef struct counters 
{
	countersNode_t* head;
}counters_t;




/*
Function: make a new countersNode
Parameters: int key, the integer used to reference the counter
Returns: countersNode_t* to the countersNode, or NULL upon malloc failure
*/

static countersNode_t* countersNode_new(int key)
{
	countersNode_t* new = malloc(sizeof(countersNode_t));
	if (new == NULL){
		return NULL;
	}

	new->next = NULL;
	new->key = key;
	new->count = 1;

	return new;
}


/*
Function: make a new counters
Parameters: (void)
Returns: counters_t* to the counters, or NULL upon malloc failure
*/
counters_t* counters_new(void)
{
	counters_t* new = malloc(sizeof(counters_t));
	if (new == NULL){
		return NULL;
	}
	new->head = NULL;

	return new;
}


/*
Function: find a node with matching key, if any
Parameters: counters_t* ctrs, the target counters
            int key, the key to be matched
Returns: a countersNode_t* to the matched node, or NULL if none exists
*/
static countersNode_t* nodeSearch(counters_t* ctrs, int key)
{
	countersNode_t* node = ctrs->head;
	countersNode_t* temp = NULL; 

	while (node != NULL){
		if (node->key == key){
			return node;
		}
		temp = node->next;
		node = temp;
	}
	return NULL;
}

/*
Function: add a counter to the counters
Parameters: counters_t* ctrs, the target counters
            int key, the key for the new counter
Returns: (void)
*/

void counters_add(counters_t* ctrs, int key)
{
    countersNode_t* prevP = NULL;
	countersNode_t* node = ctrs->head;
	countersNode_t* temp = NULL; 

	while (node != NULL){
		if (node->key == key){
			break;
		}
		prevP = node;
		
		temp = node->next;
		node = temp;
	}
	// At the end of this loop, node will either be NULL or the desired node
	// if node==NULL, prevP points to the LAST -- this is where to insert new
	//                                  `-- or NULL (make it ctrs->head)
	
	if (node == NULL){
		countersNode_t* new = countersNode_new(key);
		new->next = NULL;
		
		if (prevP == NULL) ctrs->head = new;
		else prevP->next = new;
		
	}else{
	    printf("found existing key %d\n", key);
		node->count++;
	}
}

/*
Function: get a counter that matches the key, if any
Parameters: counters_t* ctrs, the target counters
            int key, the key to be matched
Returns: the count of the matched counter, or 0 if none exists
*/
int counters_get(counters_t* ctrs, int key)
{
	countersNode_t* probe = nodeSearch(ctrs, key);

	if (probe != NULL){
		return probe->count;
	}else{
		return 0;
	}
}

/*
Function: delete the counters
Parameters: counters_t* ctrs, the target counters
Returns: (void)
*/
void counters_delete(counters_t* ctrs)
{
	countersNode_t* node = ctrs->head;
	countersNode_t* temp = NULL; 

	while (node != NULL){
		temp = node->next;
		free(node);
		node = temp;
	}

	free(ctrs);
}


/* Set value of the counter indicated by key.
 * If the key does not yet exist, create a counter for it
 * and initialize its counter value to 'count'.
 * NULL counters is ignored.
 */
void counters_set(counters_t *ctrs, int key, int count)
{
    if (ctrs == NULL){return;}
    countersNode_t* node = NULL;
    
    if ( (node = nodeSearch(ctrs, key)) != NULL){
        node->count = count;   
    } else {
        node = countersNode_new(key);                   // Make new node
        node->count = count;                            // set count
        
		node->next = ctrs->head;                        // link up
		ctrs->head = node;
    }
}

/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 */
void counters_iterate(counters_t *ctrs,
            void (*itemfunc)(void *arg, const int key, int count),
		    void *arg)
{
	countersNode_t* node = ctrs->head;
	countersNode_t* temp = NULL; 

	while (node != NULL){
	    temp = node->next;
	    itemfunc(arg, node->key, node->count);
	    
	    node = temp;
	}
}



