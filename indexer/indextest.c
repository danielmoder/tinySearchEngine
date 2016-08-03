/* 
indextest - load an index, and save it, to test those functions

Name, Summer 2016
*/
 

#include "index.h"

// Copied from http://cboard.cprogramming.com
char* strdup(char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup)
    {
        strcpy(dup, str);
    }
    return dup;
}


// Adapted from stackoverflow.com
char* readFile(FILE* file)
{
    char *buffer = NULL;
    size_t size = 0;
    
    fseek(file, 0, SEEK_END);
    size = ftell(file);

    rewind(file);

    buffer = malloc((size + 1) * sizeof(*buffer)); 
    
    fread(buffer, size, 1, file);
    
    buffer[size] = '\0';

    return buffer;
}


// index_t returned must be free'd by another function
 index_t* index_load(char* indexFileName)
 { 
    printf("in load\n");
    FILE* fp = NULL;
    if ( (fp = fopen(indexFileName, "r")) == NULL){
        printf("Error: could not open file %s\n", indexFileName);
        return NULL;
    }
    char* indexString = readFile(fp);    
    printf("read file\n");
    
    int NUMSLOTS = 4;
    index_t* index = index_new(NUMSLOTS, (void (*)(void*))counters_delete); // put the fPointer cast in index_new (it will be that for every index)
    
    char* word = NULL; // will be either keyword, docID, or count
    int pos = 0;
    
    char* keyword = NULL;
    int fileID = -1;
    int count = -1;
    
    while ( (pos = GetNextWord(indexString, pos, &word)) != 0){ // to handle the keyWORDS
        printf("in GetNextWord loop \n");

        if (word == NULL){
            free(indexString);
            free(keyword);
            fclose(fp);
            return index;
        }
        if (keyword == NULL){
            keyword = strdup(word);
        } else if (fileID == -1){
            fileID = atoi(word);
        } else {
            count = atoi(word);
        }
        
        if ( (keyword != NULL) && (fileID != -1) && (count != -1)){
            counters_t* ctr = counters_new();
            counters_set(ctr, (int)fileID, (int)count);
            index_insert(index, word, ctr);
            
            keyword = NULL;
            fileID = -1;
            count = -1;
        }
        free(word);
    }
    return NULL; //error -- should not reach this
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
 