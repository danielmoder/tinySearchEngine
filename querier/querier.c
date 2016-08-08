/*
A search engine query program

Daniel Moder, Summer 2016
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "../common/index.h"
#include "../lib/hashtable/hashtable.h"
#include "../lib/set/set.h"
#include "../lib/counters/counters.h"



// Declare functions here:
int cleanQuery(char* queryLine, char** queryArray); 
            // will return number of items in array

set_t* parseQuery(char** queryArray, int arrayIdx);

counters_t* score(set_t* parseTree);

void ctrFunc(void *arg, const int key, int count);           // called on counters

void andFunc(void *arg, const char *key, void* ctr);        // to be called on each andSet

void orFunc(void *parseTree, const char *key, void *data);  // to be called in on orSet


//

int main(int argc, char* argv[])
{

    printf(" \n");
    // Validate arguments
    // char* pageDirectory = argv[1];
    // char* indexFileName = argv[2];
    
    // Load index from argv
    index_t* index = index_load("../indexer/indexFile");

// ASSUMPTION: inLine cannot be greater than 100 characters
//              (this would also solve the array size problem for tokened input)
    
    char queryLine[100];
    // read-in loop
    while ( fgets(queryLine, sizeof(queryLine), stdin) != NULL){
        const int arraySize = 50;
        char* queryArray[arraySize];
        
// CLEAN________________________________________
        int arrayIdx = 0;
        char* word = strtok(queryLine, " ");
        
        while ( word != NULL){ // get all words in query
        
            int i = 0;
            while (word[i] != '\0'){
                word[i] = tolower(word[i]);
                if (word[i] == '\n'){
                    word[i] = '\0';
                    break;
                }else if (word[i] < 'a' || word[i] > 'z'){
                    printf("Error: invalid character (%c)\n", word[i]);
                    return 1;
                } 
                i++;
            }
            queryArray[arrayIdx] = word;
            arrayIdx++;
            
            word = strtok(NULL, " ");
        }
        // return (arrayIdx);
        
        if (arrayIdx == 0){
            continue;
        }

// CHECKLINE________________________________________
        char* prev = queryArray[0];
        char* curr;

        // check for leading/trailing and/or
        char* last = queryArray[(arrayIdx-1)];
        if (strcmp(prev, "and") == 0){
            printf("Error: invalid query\n");
            continue;
        }
        if (strcmp(prev, "or") == 0){
            printf("Error: invalid query\n");
            continue;
        }
        if (strcmp(last, "and") == 0){
            printf("Error: invalid query\n");
            continue;
        }
        if (strcmp(last, "or") == 0){
            printf("Error: invalid query\n");
            continue;
        }
        
        // preliminary run-through (check for aa/ao/oa/oo)
        for (int i = 1; i < arrayIdx; i++){
            curr = queryArray[i];
            
            if ( ((strcmp(curr, "and") == 0) || (strcmp(curr, "or") == 0)) &&
                 ((strcmp(prev, "and") == 0) || (strcmp(prev, "or") == 0)) ) {
                
                printf("Error: invalid query\n");
                continue;
            }
            prev = curr;
        }
        
// PARSE__________________________________________________________(index, query array, query index) -> orSet
        set_t* orSet = set_new(free);    
        // destructor will really be something like (?)
        // set_iterate { (counters_delete); free(set); } to free all the andSets
        
        set_t* andSet = set_new((void(*)(void *))counters_delete);
        set_insert(orSet, "start", andSet);
        
        
        word = NULL;
        
        for (int i = 0; i < arrayIdx; i++){
            word = queryArray[i];
            if (strcmp(word, "or") == 0){
                andSet = set_new((void(*)(void *))counters_delete);
                set_insert(orSet, word, andSet);
                continue;
            } else if (strcmp(word, "and") == 0){
                continue;
            }
            
            // what if index does not have value for word?
            // check if ctr == null in RANK (if so, = 0)
            counters_t* ctr = index_find(index, word);
            if (ctr != NULL){
                set_insert(andSet, word, ctr);
            } 
        }

// SCORE ____________________________________________________________________ (orSet) -> 
        
        set_iterate(orSet, orFunc, NULL);
    }

}

counters_t* score(set_t* orSet)
{
/*
    counters_t* queryScore = counters_new(free);
    set_iterate(orSet, orFunc, queryScore);
    return queryScore;
*/
    return NULL;
}

// to be called in ** orSet_iterate ** ---- called on each andSet
void orFunc(void *arg, const char *key, void *andSet)  
{

    printf("next andSet iterating...\n");
    set_iterate(andSet, andFunc, NULL);
/* 
    counters_t* andScore = counters_new(free);
    set_iterate(andSet, andFunc, andScore);
    
*/
}

// to be called in ** andSet_iterate **
void andFunc(void *arg, const char *key, void* ctr)              
{
    printf("\tin andSet, counter '%s'..\n", key);
    counters_iterate(ctr, ctrFunc, NULL);
}

void ctrFunc(void *arg, const int key, int count)
{
    printf("\t\t%d : %d \n", key, count);

}


