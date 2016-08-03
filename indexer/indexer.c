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


// assumes arg is an _open_ FILE*
void ctrFunc(void *arg, const int key, int count)
{
    fprintf(arg, "%d %d ", key, count);
}

// assumes arg is an _open_ FILE*
void setFunc(void *arg, const char *key, void *data)
{
    fprintf(arg, "%s ", key);
    // printf("iterating through counters: %s\n", key);
    counters_iterate(data, ctrFunc, arg);
    fprintf(arg, "\n");
}

bool parse(int argc, char* argv[])
{
  return true;
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

int main(int argc, char* argv[]){
  int NUMSLOTS = 4;
  
  parse(argc, argv);

  char* pageDirectory = argv[1];
  char* fileName = argv[2];
  
  void (*)(void *) cd = counters_delete;
  index_t* index = index_new(NUMSLOTS, cd);
  index_build(index, "../data/output");

  index_save(index, "indexFile.txt");
  
  index_delete(index);

  return 0;
}




