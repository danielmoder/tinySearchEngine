/* 
 * index - a set of functions for creating, saving, loading the index
 * 
 * See index.h for interface descriptions.
 * 
 * Name, Summer 2016
 */

/*  write your implementation of the functions exposed in index.h   */
#include <stdio.h>
#include <stdbool.h>
#include "../lib/hashtable/hashtable.h"
#include "../lib/counters/counters.h"

#include "index.h"
#include "webpage.h"
#include "word.h"
#include "web.h"

// assumes arg is an _open_ FILE*
static void ctrFunc(void *arg, const int key, int count)
{
    fprintf(arg, "%d %d ", key, count);
}

// assumes arg is an _open_ FILE*
static void setFunc(void *arg, const char *key, void *data)
{
    fprintf(arg, "%s ", key);
    // printf("iterating through counters: %s\n", key);
    counters_iterate(data, ctrFunc, arg);
    fprintf(arg, "\n");
}

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
        if (word == NULL)return;
        word = NormalizeWord(word);
        
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

void index_save(index_t* index, char* fileName)
{
    FILE* fp = NULL;
    if ( (fp = fopen(fileName, "w")) == NULL){
        printf("Error: could not open file %s\n", fileName);
        return;
    }
    hashtable_iterate(index, setFunc, fp);
    fclose(fp);
}

// index_t returned must be free'd by another function
 index_t* index_load(char* indexFileName)
{ 
    FILE* fp = NULL;
    if ( (fp = fopen(indexFileName, "r")) == NULL){
        printf("Error: could not open file %s\n", indexFileName);
        return NULL;
    }
    
    int NUMSLOTS = 4;
    index_t* index = index_new(NUMSLOTS, (void (*)(void*))counters_delete); // put the fPointer cast in index_new (it will be that for every index)
    
    char keyword[256];
    char dummy;
    int fileID, count;
    
    while (fscanf(fp, "%s", keyword) == 1){ // found keyword
        counters_t* ctr = counters_new();
        
        while (fscanf(fp, "%d %d%c", &fileID, &count, &dummy) == 3){
            counters_set(ctr, fileID, count);
            index_insert(index, keyword, ctr);
            
// WHY DON'T I NEED THIS?
//            if (dummy == '\n'){
  //              // Free()s necessary? I guess we'll see...
    //            printf("hey look its a new liiiine. oh shit waddup\n");
      //          break;
        //    }
        }
    }
    fclose(fp);
    return index;    
}

