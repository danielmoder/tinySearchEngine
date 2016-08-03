/* 
 * indextest - load an index, and save it, to test those functions
 *
 * 
 * Name, Summer 2016
 */

#include "indexer.c"

// Adapted from stackoverflow.com
char* readFile(FILE* file)
{
    char *buffer = NULL;
    size_t size = 0;
    
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    rewind(fp);

    buffer = malloc((size + 1) * sizeof(*buffer)); 
    
    fread(buffer, size, 1, fp);
    
    buffer[size] = '\0';

    return buffer;
}


// index_t returned must be free'd by another function
 index_t* index_load(char* indexFileName)
 {
    FILE* fp = NULL;
    if ( (fp = fopen(indexFileName, "r")) == NULL){
        printf("Error: could not open file %s\n", indexFileName);
        return;
    }
    char* indexString = readFile(fp);    
    
    NUMSLOTS = 4;
    index_t* index = index_new(NUMSLOTS, (void (*)(void*))counters_delete); // put the fPointer cast in index_new (it will be that for every index)
    
    char* word = NULL; // will be either keyword, docID, or count
    int pos = 0;
    
    while ( (pos = GetNextWord(indexString, pos, &word)) != 0){ // to handle the keyWORDS
        if (word == NULL){
            free(indexString);
            fclose(fp);
            return;
        }
        
        int fileID = 0;
        int count = 0;
        char in;
        while ( (strcmp( (fileID = (int)fgetc(fp)) , "\n") != 0)){
            count = (int)fgetc(fp);
            
            // will need to make a new counter for each line
            ctr = counters_new();
            counters_set(ctr, fileID);
            index_insert(index, word, ctr);
            
            pos+=4;                 // keep track!
        }
        pos++;
        free(word);
    }
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
 