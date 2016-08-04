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
    printf("in strndup\n");
    char* ret = malloc(len);
    if (! ret) return NULL;
    
    for (int i = 0; i < len; i++){
        ret[i] = str[i];
        printf(" at index %d / %d\n", i, len);
    }
    printf("about to set the last char...\n");
    ret[len-1] = '\0';
    
    return ret;
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
    char* fileID = NULL;
    char* count = NULL;
    
    int start, len;
    char* valP = NULL;
    
    // Ignores numbers! how convenient...
    while ( (pos = GetNextWord(indexString, pos, &word)) != 0){
        printf("just got word: %s... pos = %d\n", word, pos);
        printf("indexString[pos] = %c\n", indexString[pos]);
        if (word == NULL){
            free(indexString);
            free(keyword);
            fclose(fp);
            return index;
        }
        keyword = strdup(word);
        printf("keyword = %s\n", keyword);
        
        start = ++pos; // points to first digit of fileID
        while (indexString[pos] != ' '){
            pos++;
        } printf("out of fileID iteration loop\n");
        len = pos - start + 1;
        valP = indexString[start];
        fileID = strndup(valP, len);
        printf("fileID in int form: %d\n", atoi(fileID));
/*        
        counters_t* ctr = counters_new();
        counters_set(ctr, atoi(fileID), atoi(count));
        index_insert(index, word, ctr);
                
        free(keyword);
        free(fileID);
        free(count);
                
        keyword = NULL;
        fileID = NULL;
        count = NULL;*/
    }
    free(word);
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
 