/*
hashtable.c         Daniel Moder        July 2016
This file contains definitions for a hashtable struct. 
It also includes functions:
    hashtable_new
    hashtable_insert
    hashtable_find
    hashtable_delete
*/


#include "../set/set.h"
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


/*
Function: create a new hashtable
Parameters: const int numSlots, the number of slots for the hashtable
            void (*destructor)(void*), a function to handle the users data
Returns: a hashtable_t* to the new hashtable, or NULL upon malloc failure
*/
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

		if (new->array[i] == NULL){
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

/*
Function: insert a new key/data pair into the hashtable
Parameters: hashtable_t* hash, the target hashtable
            char* key, the string to reference the data
            void* data, the user's data
Returns: true upon successful insertion, false if pair exists or upon failure
*/
bool hashtable_insert(hashtable_t* hash, char* key, void* data)
{
	if (hash == NULL){
		return false;
	}
	unsigned long hashNum = JenkinsHash(key, (unsigned long)hash->numSlots);
	set_t* set = hash->array[(int)hashNum];

	if (! set_insert(set, key, data)){
		return false;												
	}
	return true;
}


/*
Function: find an item with desired key
Parameters: hashtable_t* hash, the target hashtable
            char* key, the reference key
Returns: a pointer the key-matched data, or NULL if it does not exist
*/
void* hashtable_find(hashtable_t* hash, char* key)
{
	unsigned long hashNum = JenkinsHash(key, (unsigned long)hash->numSlots);	// This is the set it would be in if it exists
	set_t* set = hash->array[(int)hashNum];

	void* ret = set_find(set, key);

	return ret;
}

/*
Function: deletes the hashtable
Parameters: hashtable_t* hash, the target hashtable
Returns: (void)
*/
void hashtable_delete(hashtable_t* hash)
{
	for (int i = 0; i < hash->numSlots; i++){
		set_delete(hash->array[i]);
	}
	free(hash->array);
	free(hash);
}

/* Iterate over all items in hashtable (in undefined order):
 * call itemfunc for each item, with (arg, key, data).
 */
void hashtable_iterate(hashtable_t *ht, 
		       void (*itemfunc)(void *arg, const char *key,void *data),
		       void *arg)
{
    for (int i = 0; i < ht->numSlots; i++){
        set_iterate(ht->array[i], itemfunc, arg);
    }
}



