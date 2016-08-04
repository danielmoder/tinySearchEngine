/* 
indextest - load an index, and save it, to test those functions

Name, Summer 2016
*/
#include "index.h"
 
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
 