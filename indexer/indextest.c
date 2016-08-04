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

// I wrote this one!
// expects that len is length+1 for null

char* strndup(char* str, int len)
{
    char* ret = malloc(len);
    if (! ret) return NULL;
    
    for (int i = 0; i < len; i++){
        ret[i] = str[i];
    }
    ret[len-1] = '\0';
    return ret;
}

// consistent with (indexString, pos) values available
static void parseNums(char* string, int start)
{
    fileID(


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
    FILE* fp = NULL;
    if ( (fp = fopen(indexFileName, "r")) == NULL){
        printf("Error: could not open file %s\n", indexFileName);
        return NULL;
    }
    
    int NUMSLOTS = 4;
    index_t* index = index_new(NUMSLOTS, (void (*)(void*))counters_delete); // put the fPointer cast in index_new (it will be that for every index)
    
    char string[256];
    
    char dummy;    
    char fileID[64];
    char count[64];
    
    while (fscanf(fp, "%s", string) != 0){ found
        counters_t* ctr = counters_new();
        
        while (fscanf(fp, "%d %d%c", &fileID, &count, &dummy) == 3){
            counters_set(ctr, atoi(fileID), atoi(count));
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
 