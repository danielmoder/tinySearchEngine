/* 
 * indexer - a simple web indexer
 *
 * Name, Summer 2016
 */

#include <stdio.h>
#include <stdbool.h>

#include "../common/index.h"
#include "../common/webpage.h"
#include "../common/word.h"
#include "../lib/memory/memory.h"
#include "../lib/hashtable/hashtable.h"



void ctrFunc(void *arg, const int key, int count)
{
    printf("key: %d, count: %d\n", key, count);
}

void setFunc(void *arg, const char *key, void *data)
{
    printf("iterating through counters: %s\n", key);
    counters_iterate(data, ctrFunc, NULL);
}

bool parse(int argc, char* argv[])
{
  printf("parsed\n");
  return true;
}

void index_page(index_t* index, WebPage* page, int fileID)
{
    char* word = NULL;
    int pos = 0;
    
    while ( (pos = GetNextWord(page->html, pos, &word)) != 0){
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


int main(int argc, char* argv[]){
  int NUMSLOTS = 4;
  
  parse(argc, argv);
  
  
  

  char* pd = argv[1];
  char* fn = argv[2];


  
  index_t* index = index_new(NUMSLOTS, count_free);
  index_build(index, "~/cs50/labs/tse/data/output");
  
  printf("iterating through index\n");
  hashtable_iterate(index, setFunc, NULL);
  
  count_free(index);  

  return 0;

}




