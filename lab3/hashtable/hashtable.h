#ifndef __HASHTABLE_H
#define	__HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct hashtable hashtable_t;

hashtable_t* hashtable_new(const int numSlots, void (*destructor)(void*));

bool hashtable_insert(hashtable_t* hash, char* key, void* data);

void* hashtable_find(hashtable_t* hash, char* key);

void hashtable_delete(hashtable_t* hash);

#endif // __HASHTABLE_H