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

/*
Function: determine if indexer was given valid inputs
Parameters: (int argc, char* argv[]), from main
Return: true if valid, false otherwise
*/
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
Function: build an index based on the html of a directory of crawler files,\
            and write an indexFile based on that index object
Parameters: char* dataDirectory,
            char* outFile
Return: 0 on success, -1 if invalid arguments
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




