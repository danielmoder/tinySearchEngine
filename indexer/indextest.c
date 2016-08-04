/* 
indextest - load an index, and save it, to test those functions

Name, Summer 2016
*/
#include "index.h"


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
 