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

countersNode_t* countersNode_new(int key)
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

counters_t* counters_new(void)
{
	counters_t* new = malloc(sizeof(counters_t));
	if (new == NULL){
		return NULL;
	}

	new->head = NULL;

	return new;
}


// return the node if it matches the key, 
// otherwise return NULL
countersNode_t* nodeSearch(counters_t* ctrs, int key)
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


void counters_add(counters_t* ctrs, int key)
{
	countersNode_t* probe = nodeSearch(ctrs, key);

	if (probe == NULL){									// counter with key DNE -> make it!
		countersNode_t* new = countersNode_new(key);
		new->next = ctrs->head;
		ctrs->head = new;
	}else{
		probe->count++;
	}
}

int counters_get(counters_t* ctrs, int key)
{
	countersNode_t* probe = nodeSearch(ctrs, key);

	if (probe != NULL){
		return probe->count;
	}else{
		return 0;
	}
}

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
