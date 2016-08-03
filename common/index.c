/* 
 * index - a set of functions for creating, saving, loading the index
 * 
 * See index.h for interface descriptions.
 * 
 * Name, Summer 2016
 */

/*  write your implementation of the functions exposed in index.h   */

#include "index.h"
#include "webpage.h"
#include "word.h"

index_t* index_new(int numSlots, void (*destructor)(void*))
{
    index_t* new = hashtable_new(numSlots, destructor);
    return new;
}

void index_insert(index_t* index, char* keyword, counters_t* ctr)
{
  hashtable_insert(index, keyword, ctr);
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


void index_page(index_t* index, WebPage* page, int fileID)
{
    char* word = NULL;
    int pos = 0;
    
    while ( (pos = GetNextWord(page->html, pos, &word)) != 0){
        if (word == NULL){return;}
        counters_t* ctr = index_find(index, word);
        
        if (ctr == NULL){
            ctr = counters_new();
            index_insert(index, word, ctr);
        }
        counters_add(ctr, fileID);
        
        free(word);
    }
}

void index_build(index_t* index, char* pageDirectory)
{

    WebPage* page;
    int fileID = 0;
    
    while ( (page = webpage_load(pageDirectory, fileID)) != NULL){
        index_page(index, page, fileID);
        
        webpage_delete(page);
        fileID++;
    }
    
}

void index_save(index_t* index, char* fileName, void (*setFunc)(void*) )
{
    FILE* fp = NULL;
    if ( (fp = fopen(fileName, "w")) == NULL){
        printf("Error: could not open file %s\n", fileName);
        return;
    }
    hashtable_iterate(index, setFunc, fp);
    fclose(fp);
}


