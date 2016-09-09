/* 
 * index - a set of functions for creating, saving, loading the index
 * 
 * The index is keyed by words (strings) and stores counter sets; 
 * each counter set represents the set of documents where that word 
 * appeared, and the number of occurrences of that word in each document.
 * 
 * Daniel Moder, Summer 2016
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>
#include "../lib/hashtable/hashtable.h"
#include "../lib/counters/counters.h"

#include "index.h"
#include "webpage.h"
#include "word.h"
#include "web.h"

/**************** global types ****************/

// index_t will be hashtable_t of counters (set of sets of counters)
typedef hashtable_t index_t;

/********** add function prototypes here *********/
index_t* index_new(int numSlots, void (*destructor)(void*));
void index_insert(index_t* index, char* keyword, counters_t* ctr);
counters_t* index_find(index_t* index, char* keyword);
void index_delete(index_t* index);
void index_page(index_t* index, WebPage* page, int fileID);
void index_build(index_t* index, char* pageDirectory);
void index_save(index_t* index, char* fileName);
index_t* index_load(char* indexFileName);




#endif // __INDEX_H
