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

//returns --> pointer to the data in the key-matched node if it exists 
//      `---> NULL if not
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