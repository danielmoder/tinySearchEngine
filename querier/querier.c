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

typedef struct node
{
    int docID;
    int score;
}node_t;

// Declare functions here:
int cleanQuery(char* queryLine, char** queryArray);

// Builds (set(set(counters)))
// `---> (query(andPhrases(wordCounters)))
set_t* parseQuery(char** queryArray, int arrayIdx);

// Score() + helper iteratorFuncs
counters_t* score(set_t* parseTree);

void orFunc(void *parseTree, const char *key, void *data);
void andFunc(void *arg, const char *key, void* ctr);
void andHelp(void *ctr, const int key, int count);

void maxCtrFunc(void *andScore, const char *key, void *ctr);
void maxCtrHelper(void* andScore, const int key, int count);

void addFunc(void *queryScore, const int key, int count);
void leastFunc(void *ctr, const int key, int count);

void qTestFunc(void* arg, const int key, int count);
void matchCount(void* matches, const int key, int count);
void arrayFill(void* array, const int key, int count);
int sortFunc(const void *a, const void *b);


//

int main(int argc, char* argv[])
{
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
        char* queryCopy = malloc(strlen(queryLine)+1);
        strcpy(queryCopy, queryLine);
        
        const int arraySize = 50;
        char* queryArray[arraySize];
        
// CLEAN________________________________________(queryLine, queryArray)
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

// OUTPUT ___________________________________________________________________
        printf("Query: %s\n", queryCopy);
        free(queryCopy);
        
        counters_t* matchesCounter = counters_new();
        counters_iterate(queryScore, matchCount, matchesCounter);
        int matches = counters_get(matchesCounter, 0);
        
        if ( matches == 0){
            printf("No documents matched\n");
            continue;
        }
        
        node_t* results = malloc(sizeof(node_t) * matches);
        node_t* resultsCopy = results;
        counters_iterate(queryScore, arrayFill, resultsCopy);
        
        
        
        qsort(results, matches, sizeof(node_t), sortFunc);
        
        char* directory = "../data/output";
        results -= (sizeof(node_t) * matches);
        
        for (int i = 0; i < matches; i++){
            node_t current = results[i];
            int key = current.docID;
            int score = current.score;
            
            char filepath[128];
            sprintf(filepath, "%s%s%d", directory, "/", key);
        
            FILE* fp = fopen(filepath, "r");
            if (fp != NULL){
                char URL[128];
                fgets(URL, 128, fp);
                printf("docID %d: score of %d. URL = %s\n", key, score, URL);
            }
        }
        
        // taking "../data/output" as page directory
        
        //counters_iterate(queryScore, qTestFunc, directory);
    }
}

// -------------------------------------------------------------------------------------------





// Called on each andSet
// Accumulates queryScore as andScores are determined
void orFunc(void *queryScore, const char *key, void *andSet)  
{
    counters_t* andScore = counters_new();
    set_iterate(andSet, maxCtrFunc, andScore);  // MAX andScore
    set_iterate(andSet, andFunc, andScore);     // reduce andScore

    // update queryScore w/ each andPhrase's score as they are calculated
    counters_iterate(andScore, addFunc, queryScore);
}

// Called on each counterNode of the andScore to be added to queryScore
// Adds documents' andScores to queryScore
void addFunc(void *queryScore, const int key, int count)
{
    int qScore = counters_get(queryScore, key);
    qScore += count;
    counters_set(queryScore, key, qScore);
}


// Called on each counters_t object in andSet (wordCounters)
//      andHelp makes wordCounter domain match andScore domain
//      leastFunc takes smaller b/t andScore[key] and ctr[key]
void andFunc(void *andScore, const char *key, void* ctr)              
{
    counters_iterate(andScore, andHelp, ctr);
    counters_iterate(ctr, leastFunc, andScore);
}

void andHelp(void *ctr, const int key, int count)
{
    int val = counters_get(ctr, key);
    counters_set(ctr, key, val);
}

void leastFunc(void *andScore, const int key, int count)
{
    int andCount = counters_get(andScore, key);
    if (count < andCount){
        counters_set(andScore, key, count);
    }
}


// Sets the contents of andScore as follows:
//      domain(docIDs) = UNION of docIDs in andSet
//      range(counts) = INT_MAX (2147483647)
void maxCtrFunc(void *andScore, const char* key, void* ctr)
{
    counters_iterate(ctr, maxCtrHelper, andScore);
}

// Helper to above
void maxCtrHelper(void* andScore, const int key, int count)
{
    counters_set(andScore, key, INT_MAX);
}

// Called on each node of queryScore
// If score > 0 (match), increment matches
void matchCount(void* matchesCounter, const int key, int count)
{
    if (count > 0){
        counters_add(matchesCounter, 0);
    }
}

// Called on each item of queryScore
// fills array with (docID, score) nodes
void arrayFill(void* array, const int key, int count)
{
    if (count > 0){
        node_t* new = malloc(sizeof(node_t));
        new->docID = key;
        new->score = count;
        
        *(node_t*)array = *new;
        array = array + sizeof(node_t);
    }
}

int sortFunc(const void *a, const void *b)
{
    node_t nodeA = *(const node_t*)a;
    node_t nodeB = *(const node_t*)b;
    
    int aScore = nodeA.score;
    int bScore = nodeB.score;
    
    if (aScore < bScore){
        return 1;
    } else if (aScore < bScore){
        return -1;
    } return 0;
}

void qTestFunc(void* directory, const int key, int count)
{
    if (count > 0){
        char filepath[128];
        sprintf(filepath, "%s%s%d", (char*)directory, "/", key);
        
        FILE* fp = fopen(filepath, "r");
        if (fp != NULL){
            char URL[128];
            fgets(URL, 128, fp);
            printf("docID %d: score of %d. URL = %s\n", key, count, URL);
        }
    }
}
