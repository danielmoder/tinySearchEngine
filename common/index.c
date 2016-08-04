/* 
 * index - a set of functions for creating, saving, loading the index
 * 
 * See index.h for interface descriptions.
 * 
 * Daniel Moder, Summer 2016
 */

#include <stdio.h>
#include <stdbool.h>
#include "../lib/hashtable/hashtable.h"
#include "../lib/counters/counters.h"

#include "index.h"
#include "webpage.h"
#include "word.h"
#include "web.h"

/*
Function: format counterNode data and write to a file
Parameters: void *arg, an opened FILE*
            const int key, the fileID of the counter
            int count, the number of occurrences of the word
Return: (void)
*/
static void ctrFunc(void *arg, const int key, int count)
{
    fprintf(arg, "%d %d ", key, count);
}

/*
Function: format setNode data and write to a file
Parameters: void *arg, an opened FILE*
            const char *key, the keyword of the setNode
            void *data, the counters_t object
Return: (void)
*/
static void setFunc(void *arg, const char *key, void *data)
{
    fprintf(arg, "%s ", key);
    // printf("iterating through counters: %s\n", key);
    counters_iterate(data, ctrFunc, arg);
    fprintf(arg, "\n");
}

/*
Function: make a new index
Parameters: int numSlots, the number of slots in the hashtable
            void (*destructor)(void*), a function to free the counters
Return: pointer to new index
*/
index_t* index_new(int numSlots, void (*destructor)(void*))
{
    index_t* new = hashtable_new(numSlots, destructor);
    return new;
}

/*
Function: insert a counter to the index
Parameters: index_t* index, 
            char* keyword, 
            counters_t* ctr
Return: (void)
*/
void index_insert(index_t* index, char* keyword, counters_t* ctr)
{
  hashtable_insert(index, keyword, ctr);
}

/*
Function: find a counters_t object in an index, if it exists
Parameters: index_t* index, 
            char* keyword
Return: a pointer to the counters_t object
*/
counters_t* index_find(index_t* index, char* keyword)
{
    counters_t* ret = hashtable_find(index, keyword);
    return ret;
}

/*
Function: delete the index
Parameters: index_t* index
Return: (void)
*/
void index_delete(index_t* index)
{
    hashtable_delete(index);
}

/*
Function: index all of the words on a page
Parameters: index_t* index, 
            WebPage* page, webpage object from the crawler file
            int fileID, number corresponding to the file
Return: (void)
*/
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

/*
Function: build an index from a directory of crawler webFiles
Parameters: index_t* index, 
            char* pageDirectory
Return: (void)
*/
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

/*
Function: write the indexFile
Parameters: index_t* index, 
            char* fileName
Return: (void)
*/
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

/*
Function: loads and builds an index object from a text indexFile
Parameters: char* indexFileName
Return: a pointer to the index
*/
index_t* index_load(char* indexFileName)
{ 
    FILE* fp = NULL;
    if ( (fp = fopen(indexFileName, "r")) == NULL){
        printf("Error: could not open file %s\n", indexFileName);
        return NULL;
    }
    
    int NUMSLOTS = 4;
    index_t* index = index_new(NUMSLOTS, (void (*)(void*))counters_delete); 
    
    char keyword[256];
    char dummy;
    int fileID, count;
    
    while (fscanf(fp, "%s", keyword) == 1){ // found keyword
        counters_t* ctr = counters_new();
        
        while (fscanf(fp, "%d %d%c", &fileID, &count, &dummy) == 3){
            counters_set(ctr, fileID, count);
            index_insert(index, keyword, ctr);

        }
    }
    fclose(fp);
    return index;    
}

