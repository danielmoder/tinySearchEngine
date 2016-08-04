/* 
indextest - load an index, and save it, to test those functions

Daniel Moder, Summer 2016
*/
#include "index.h"
 
 /*
 Function: take in an indexFile, construct a new index, and save the new one
 Parameters: int argc, char* argv[]
 Return: 0 on success, -1 if invalid parameters
 */
 
 int main(int argc, char* argv[])
 {
    if (argc != 3){
        printf("Error: indextest takes exactly 2 arguments\n");
        return -1;
    }
    
    char* indexFileName = argv[1];
    index_t* index = index_load(indexFileName);

    index_save(index, argv[2]);
    index_delete(index);
    return 0;
 }
 