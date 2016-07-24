#include "set.h"
#include "jhash.h"
#include "hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct hashtable {
	int numSlots;
	set_t** array;
	void (*destructor)(void* data);
}hashtable_t;

hashtable_t* hashtable_new(const int numSlots, void (*destructor)(void*))
{
	hashtable_t* new = malloc( sizeof(hashtable_t) );
	if (new == NULL){
		return NULL;
	}
	new->destructor = destructor;
	new->numSlots = numSlots;

	int arraySize = (numSlots * sizeof(set_t*));

	set_t** array = malloc(arraySize);
	if (array == NULL){
		free(new);
		return NULL;
	}
	new->array = array;

	for (int i = 0; i < numSlots; i++){
		new->array[i] = set_new(new->destructor);

		if (new->array[i] == NULL){						// Have to go back through all sets that had already been made...
			for (int b = i; b > 0; b--){
				set_delete(new->array[b]);
			}
			free(array);
			free(new);
			return NULL;
		}
	}
	return new;
}


bool hashtable_insert(hashtable_t* hash, char* key, void* data)
{
	if (hash == NULL){
		return false;
	}

	unsigned long hashNum = JenkinsHash(key, (unsigned long)hash->numSlots);
	set_t* set = hash->array[(int)hashNum];

	if (! set_insert(set, key, data)){ 											// returns false if 1. set is null, 2. set already contains key, 
		return false;															// 3. error with malloc in setNode_new
		
	}

	return true;
}

void* hashtable_find(hashtable_t* hash, char* key)
{
	unsigned long hashNum = JenkinsHash(key, (unsigned long)hash->numSlots);	// This is the set it would be in if it exists
	set_t* set = hash->array[(int)hashNum];

	void* ret = set_find(set, key);

	return ret;
}

void hashtable_delete(hashtable_t* hash)
{
	for (int i = 0; i < hash->numSlots; i++){
		set_delete(hash->array[i]);
	}
	free(hash->array);
	free(hash);
}