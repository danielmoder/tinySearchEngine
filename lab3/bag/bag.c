#include "bag.h"

#include <stdlib.h>
#include <stdio.h>

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



static bagNode_t* bagNode_new(void* data)
{
	bagNode_t* new = malloc(sizeof(bagNode_t));

	new->next = NULL;
	new->data = data;
	return new;
}



bag_t* bag_new(void (*deleteFunc)(void*) )
{
	bag_t* new = malloc(sizeof(bag_t));
	new->head = NULL;
	new->destructor = deleteFunc;

	return new;
}

void bag_insert(bag_t* bag, void* data)
{
	bagNode_t* newNode = bagNode_new(data);

	newNode->next = bag->head;
	bag->head = newNode;
}

//take from head of bag
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
