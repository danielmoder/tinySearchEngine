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
        printf("Gettin Keywords MOFO\n");
        counters_t* ctr = counters_new();
        
        while (fscanf(fp, "%d %d%c", &fileID, &count, &dummy) == 3){
            printf("adding dem counterz\n");
            counters_set(ctr, fileID, count);
            index_insert(index, keyword, ctr);
            
            if (dummy == '\n'){
                // Free()s necessary? I guess we'll see...
                printf("hey look its a new liiiine. oh shit waddup\n");
                break;
            }
        }
    }
    fclose(fp);
    return index;    
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
 