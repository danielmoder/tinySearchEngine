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




