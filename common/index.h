/* 
 * index - a set of functions for creating, saving, loading the index
 * 
 * The index is keyed by words (strings) and stores counter sets; 
 * each counter set represents the set of documents where that word 
 * appeared, and the number of occurrences of that word in each document.
 * 
 * Name, Summer 2016
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>
#include "hashtable/hashtable.h"
#include "counters/counters.h"

/**************** global types ****************/

// The index is actually a hashtable. 
typedef hashtable_t index_t;

/********** add function prototypes here *********/
index_t* index_new(numSlots, void (*destructor)(void*));
void index_insert(index_t* index, counters_t* ctr);
counters_t* index_find(index_t* index, char* keyword);
index_delete(index_t* index);



#endif // __INDEX_H
