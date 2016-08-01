/* 
 * index - a set of functions for creating, saving, loading the index
 * 
 * See index.h for interface descriptions.
 * 
 * Name, Summer 2016
 */

/*  write your implementation of the functions exposed in index.h   */

#include <index.h>

index_t* index_new(numSlots, void (*destructor)(void*))
{
    index_t* new = hashtable_new(numSlots, destructor);
    return new;
}
void index_insert(index_t* index, counters_t* ctr)
{
    hashtable_insert(index, ctr);
}

counters_t* index_find(index_t* index, char* keyword)
{
    counters_t* ret = hashtable_find(index, keyword);
    return ret;
}

void index_delete(index_t* index)
{
    hashtable_delete(index);
}


