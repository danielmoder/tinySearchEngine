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
    
    char string[256];
    char dummy;    
    int fileID, count;
    
    while (fscanf(fp, "%s", string) != 0){ // found keyword
        counters_t* ctr = counters_new();
        
        while (fscanf(fp, "%d %d%c", &fileID, &count, &dummy) == 3){
            counters_set(ctr, fileID, count);
            index_insert(index, word, ctr);
            
            if (dummy == '\n'){
                // Free()s necessary? I guess we'll see...
                break;
            }
        }
    }
    fclose(fp);
}
    
 
 int main(int argc, char* argv[])
 {
    char* indexFileName = "indexFile.txt";
    index_t* index = index_load(indexFileName);
    printf("made index.. right??\n");
    
    index_save(index, "newFile.txt");
    index_delete(index);
    return 0;
 }
 