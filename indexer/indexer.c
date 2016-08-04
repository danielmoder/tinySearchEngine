/* 
 * indexer - a simple web indexer
 *
 * Name, Summer 2016
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>



#include "../common/index.h"
#include "../common/webpage.h"
#include "../common/word.h"
#include "../lib/memory/memory.h"
#include "../lib/hashtable/hashtable.h"

bool parse(int argc, char* argv[])
{
  if (argc != 3){
    printf("Error: indexer takes exactly 2 arguments\n");
    return false;
    
  } else if ( access(argv[1], R_OK) == -1){
    printf("Error: could not find readble directory: %s\n", argv[1]);
    return false;
    
  } else if ( access(argv[2], W_OK) == -1){
    printf("Error: could not find writeable file: %s\n", argv[2]);
    return false;

  } else {
    return true;
  }
}
/*
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
*/
int main(int argc, char* argv[]){

  
  if (! parse(argc, argv)) return -1;
  
  char* dataDirectory = argv[1];
  char* outFile = argv[2];

  int NUMSLOTS = 4;  
  index_t* index = index_new(NUMSLOTS, (void (*)(void*))counters_delete);
  index_build(index, dataDirectory);

  index_save(index, outFile);
  index_delete(index);

  return 0;
}




