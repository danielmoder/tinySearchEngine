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

// Builds (set(set(counters)))
// `---> (query(andPhrases(wordCounters)))
set_t* parseQuery(char** queryArray, int arrayIdx);

// Score() + helper iteratorFuncs
counters_t* score(set_t* parseTree);

void orFunc(void *parseTree, const char *key, void *data);
void andFunc(void *arg, const char *key, void* ctr);

void maxCtrFunc(void *andScore, const char *key, void *ctr);
void maxCtrHelper(void* andScore, const int key, int count);

void addFunc(void *queryScore, const int key, int count);
void leastFunc(void *ctr, const int key, int count);

void qTestFunc(void* arg, const int key, int count);


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

// SCORE ____________________________________________________________________ 

        counters_t* queryScore = counters_new();
        set_iterate(orSet, orFunc, queryScore);
        
        counters_iterate(queryScore, qTestFunc, NULL);
    }
}

// -------------------------------------------------------------------------------------------

// called on each andSet
void orFunc(void *queryScore, const char *key, void *andSet)  
{
    counters_t* andScore = counters_new();
    set_iterate(andSet, maxCtrFunc, andScore);  // MAX andScore
    set_iterate(andSet, andFunc, andScore);     // reduce andScore

    // update queryScore w/ each andPhrase's score as they are calculated
    counters_iterate(andScore, addFunc, queryScore);
}

//Called on each counterNode of the andScore to be added to queryScore
void addFunc(void *queryScore, const int key, int count)
{
    int qScore = counters_get(queryScore, key);
    qScore += count;
    counters_set(queryScore, key, qScore);
}

// Called on each counters_t object in andSet
// Helper iterates through andScore + 
// takes smallest b/t andScore[key] and ctr[key]

void andFunc(void *andScore, const char *key, void* ctr)              
{
    counters_iterate(ctr, leastFunc, andScore);
}

// called on each counterNode in andScore, passed wordCtr
void leastFunc(void *andScore, const int key, int count)
{
    // Returns 0 if key DNE in ctr
    int andCount = counters_get(andScore, key);
    
    if (count < andCount){
        counters_set(andScore, key, count);
    }
}



// andScore{docIDs} = UNION of docIDs in andSet
// andScore{counts} = INT_MAX (2147483647)
void maxCtrFunc(void *andScore, const char* key, void* ctr)
{
    counters_iterate(ctr, maxCtrHelper, andScore);
}

void maxCtrHelper(void* andScore, const int key, int count)
{
    counters_set(andScore, key, INT_MAX);
}

void qTestFunc(void* arg, const int key, int count)
{
    printf("docID %d: score of %d\n", key, count);
}
