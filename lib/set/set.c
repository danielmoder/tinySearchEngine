/*
set.c           Daniel Moder        July 2016
This file includes definitions for a set struct. It also contains functions:
    set_new
    set_find
    set_insert
    set_delete

as well as helper functions:
    setNode_new
*/
#include "set.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct setNode {
	struct setNode* next;
	char* key;
	void* data;
}setNode_t;

typedef struct set {
	setNode_t* head;
	void (*destructor)(void* data);
}set_t;


/*
Function: create a new setNode
Parameters: char* key, the referencing key
            void* data, the user's data
Returns: a setNode_t* to the new node upon success, or NULL upon malloc failure
*/
static setNode_t* setNode_new(char* key, void* data)
{
	setNode_t* new = malloc(sizeof(setNode_t));
	if (new == NULL){
		return NULL;
	} 

	new->key = malloc(strlen(key)+1);
	if (new->key == NULL){
		free(new);
		return NULL;
	} 

	strcpy(new->key, key);
	new->data = data;
	new->next = NULL;
	return new;
}

/*
Function: create a new set
Parameters: void (*destructor)(void*), the function to free the user's data
Returns: a set_t* to the new set upon success, or NULL upon malloc failure
*/
set_t* set_new(void (*destructor)(void*) )
{
	set_t* new = malloc(sizeof(set_t));
	if (new == NULL){
		return NULL;
	}

	new->head = NULL;
	new->destructor = destructor;

	return new;
}


/*
Function: find data matched with a given key, if any
Parameters: set_t* set, the target set
            char* key, the key to be matched
Returns: a void* to the key-matched data, or NULL if none exists
*/
void* set_find(set_t* set, char* key)
{
	setNode_t* node = set->head;
	setNode_t* temp = NULL; 

	while (node != NULL){
		if (strcmp(node->key, key) == 0){
			return node->data;
		}
		temp = node->next;
		node = temp;
	}
	return NULL;
}

/*
Function: insert a key/data pair into a set
Parameters: set_t* set, the target set
            char* key, the key to be matched
            void* data, the user's data
Returns: true upon successful insertion, false if key exists or upon failure
*/
bool set_insert(set_t* set, char* key, void* data)
{
	if (set == NULL){
		return false;
	}
	else if (set_find(set, key) == NULL){ 				// key does not exist

		setNode_t* new = setNode_new(key, data);
		if (new == NULL){
			return false;
		}

		new->next = set->head;
		set->head = new;

		return true;
	}
	else{
		return false;
	}
}

/*
Function: delete the set
Parameters: set_t* set, the target set
Returns: (void)
*/
void set_delete(set_t* set)
{
	setNode_t* node = set->head;
	setNode_t* temp = NULL; 

	while (node != NULL){
		temp = node->next;

		set->destructor(node->data);
		free(node->key);
		free(node);

		node = temp;
	}

	free(set);
}

/* Iterate over all items in set (in undefined order):
 * call itemfunc for each item, passing (arg, key, data).
 */
void set_iterate(set_t *set,
		  void (*itemfunc)(void *arg, const char *key, void *data),
		  void *arg)
{
	setNode_t* node = set->head;
	setNode_t* temp = NULL; 

	while (node != NULL){
	    printf("in set_iter\n");
		temp = node->next;
		
		itemfunc(arg, node->key, node->data);
		
		node = temp;
	}
}

