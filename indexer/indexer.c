/* 
 * indexer - a simple web indexer
 *
 * Name, Summer 2016
 */

#include <stdio.h>
#include <stdbool.h>

#include "../common/index.h"
#include "../common/webpage.h"
#include "../lib/memory/memory.h"

bool parse(int argc, char* argv[])
{
  printf("parsed\n");
  return true;
}

index_t* index_build(char* pageDirectory)
{
  index_t* index = assertp(malloc(sizeof(index)), "index\n");
  
  return index;

}


int main(int argc, char* argv[]){
  parse(argc, argv);

  char* pd = argv[1];
  char* fn = argv[2];


  
  index_t* index = index_new(count_free);
  


count_free(index);  

  

  return 0;



}




