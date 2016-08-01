/*
bag.c       Daniel Moder        July 2016

This file includes the definitions of a bag struct. It includes functions:
    bag_new
    bag_insert
    bag_extract
    bag_delete
    
as well as helper functions:
    bagNode_new
*/

#include <stdlib.h>
#include <stdio.h>

#include "bag.h"


typedef struct bagNode
{
	struct bagNode* next;
	void* data;
}bagNode_t;

typedef struct bag 
{
	bagNode_t* head;
	void (*destructor)(void* data);
}bag_t;


/*
Function: make a new bagNode
Parameters: void* data, a pointer to the user's data
Returns: a bagNode_t* upon successful creation, NULL upon malloc failure
*/
static bagNode_t* bagNode_new(void* data)
{
	bagNode_t* new = malloc(sizeof(bagNode_t));
    if (new == NULL){
        return NULL;
    }
	new->next = NULL;
	new->data = data;
	return new;
}


/*
Function: make a new bag
Parameters: void (*deleteFunc)(void*), a function to handle the user's data
Returns: a bag_t* upon successful creation, NULL upon malloc failure
*/
bag_t* bag_new(void (*deleteFunc)(void*) )
{
	bag_t* new = malloc(sizeof(bag_t));
    if (new == NULL){
        return NULL;
    }
	new->head = NULL;
	new->destructor = deleteFunc;

	return new;
}

/*
Function: insert an item into bag
Parameters: bag_t* bag, the target bag
            void* data, the data pointer to be inserted
Returns: (void)
*/
void bag_insert(bag_t* bag, void* data)
{
	bagNode_t* newNode = bagNode_new(data);

	newNode->next = bag->head;
	bag->head = newNode;
}

/*
Function: extract an item from the bag
Parameters: bag_t* bag, the target bag
Returns: a void* to data if any, else NULL
*/
void* bag_extract(bag_t* bag)
{
	if (bag->head == NULL){
		return NULL;
	}
	else {
		bagNode_t* retNode = bag->head;
		void* ret = retNode->data;

		bag->head = retNode->next;
		free(retNode);

		return ret;
	}
}

/*
Function: deletes target bag, frees allocated memory, and destructs user data
Parameters: bag_t* bag, the target bag
Returns: (void)
*/
void bag_delete(bag_t* bag)
{
	bagNode_t* node = bag->head;
	bagNode_t* temp = NULL;

	while (node != NULL){
		temp = node->next;

		bag->destructor(node->data);
		free(node);

		node = temp;
	}
	free(bag);
}

/* Iterate over all items in bag (in undefined order):
 * call itemfunc for each item, passing (arg, data).
 */
void bag_iterate(bag_t *bag,
		 void (*itemfunc)(void *arg, void *data),
		 void *arg)
{
    bagNode_t* node = bag->head;
	bagNode_t* temp = NULL;

	while (node != NULL){
		temp = node->next;
		
		itemfunc(arg, node->data);
		
		node = temp;
	}
}

