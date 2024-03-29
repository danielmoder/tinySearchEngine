/*
A search engine query program

Daniel Moder, Summer 2016
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>

#include "../common/index.h"
#include "../lib/hashtable/hashtable.h"
#include "../lib/set/set.h"
#include "../lib/counters/counters.h"

typedef struct node
{
    int docID;
    int score;
}node_t;

// Functions called in main():
bool validateArgs(int argc, char* argv[]);

int cleanQuery(char* queryLine, char** queryArray);

bool checkLine(char** queryArray, int arrayIdx);

set_t* parseQuery(char** queryArray, int arrayIdx, index_t* index);

counters_t* score(set_t* parseTree);

void output(char* queryCopy, counters_t* queryScore, char* directory);


//parse() helpers:
void ctrCopy(void* ctr, const int key, int count);

// score() helpers:
void orFunc(void *parseTree, const char *key, void *data);
void andFunc(void *arg, const char *key, void* ctr);
void andHelp(void *ctr, const int key, int count);

void maxCtrFunc(void *andScore, const char *key, void *ctr);
void maxCtrHelper(void* andScore, const int key, int count);

void addFunc(void *queryScore, const int key, int count);       // union
void leastFunc(void *ctr, const int key, int count);            // intersection

// output() helpers:
void matchCount(void* matches, const int key, int count);
void arrayFill(void* array, const int key, int count);
int sortFunc(const void *a, const void *b);


// Global var macros:
#define MAX_QUERY_LEN 200


/*
Function: receive query from user and print the "most applicable" document URLS
    based on the scoring algorithm in score()
Parameters: pageDirectory, a directory of text files made by crawler
            indexFileName, an indexFile made by indexer
Return: 0 on success, -1 on failure
*/

int main(int argc, char* argv[])
{
    if (! validateArgs(argc, argv)){
        return -1;
    }

    char* pageDirectory = argv[1];
    char* indexFileName = argv[2];
    
    // Load index from indexFile
    index_t* index = index_load(indexFileName);

    char queryLine[MAX_QUERY_LEN];
    
    // read-in loop
    while ( fgets(queryLine, MAX_QUERY_LEN, stdin) != NULL){
    
        // copy query for output (original changed by strtok())
        char* queryCopy = malloc(strlen(queryLine)+1);
        strcpy(queryCopy, queryLine);
        
        const int arraySize = (MAX_QUERY_LEN/2);
        char* queryArray[arraySize];
        
        int arrayIdx = cleanQuery(queryLine, queryArray);
        
        if (arrayIdx == -1){
            free(queryCopy);
            continue;
        } else if (! checkLine(queryArray, arrayIdx)){
            free(queryCopy);
            continue;
        }
        
        set_t* orSet = parseQuery(queryArray, arrayIdx, index);
        
        counters_t* queryScore = counters_new();
        set_iterate(orSet, orFunc, queryScore);
        
        output(queryCopy, queryScore, pageDirectory);
        
        free(queryCopy);
        set_delete(orSet);
        counters_delete(queryScore);
    }
    index_delete(index);
    return 0;
}

// -----------------------------------------------------------------------------


/*
Function: verify that the 2 inputs to main() are a readable directory/file
Parameters: pageDirectory, a directory of text files made by crawler
            indexFileName, an indexFile made by indexer
Return: true if valid arguments, false otherwise
*/

bool validateArgs(int argc, char* argv[])
{
  if (argc != 3){
    printf("Error: querier takes exactly 2 arguments\n");
    return false;
    
  } else if ( access(argv[1], R_OK) == -1){
    printf("Error: could not find readable directory: %s\n", argv[1]);
    return false;
    
  } else if ( access(argv[2], R_OK) == -1){
    printf("Error: could not find readable file: %s\n", argv[2]);
    return false;

  } else {
    return true;
  }
}


/*
Function: normalize characters, determine validity of query
Parameters: char* queryLine, user's line from stdin
            char** queryArray, array to be filled word by word with query
Returns: index of array upon success (# words + 1), -1 upon invalid input
*/

int cleanQuery(char* queryLine, char** queryArray)
{
    int arrayIdx = 0;
    
    // get word, space delimited
    char* word = strtok(queryLine, " ");
    
    // loop until end of query
    while ( word != NULL){
        int i = 0;
        
        // loop until end of word
        while (word[i] != '\0'){
            word[i] = tolower(word[i]);
            
            // remove new line @ end of line, replace w null + end
            if (word[i] == '\n'){
                word[i] = '\0';
                break;
                
            // if non-alpha character, failure
            }else if (word[i] < 'a' || word[i] > 'z'){
                printf("Error: invalid character (%c)\n", word[i]);
                return -1;
            } 
            i++;
        }
        queryArray[arrayIdx] = word;
        arrayIdx++;
        
        word = strtok(NULL, " ");
    }
    if (arrayIdx == 0){
        return -1;
    }
    return (arrayIdx);
}

/*
Function: check for leading and adjacent operator keywords
Parameters: char** queryArray, array of words from user input
Returns: true if valid, false if invalid
*/

bool checkLine(char** queryArray, int arrayIdx)
{
    char* first = queryArray[0];
    char* last = queryArray[(arrayIdx-1)];
    
    // check for leading/trailing 'and'/'or'
    if (strcmp(first, "and") == 0){
        printf("Error: invalid query\n");
        return false;
    }
    if (strcmp(first, "or") == 0){
        printf("Error: invalid query\n");
        return false;
    }
    if (strcmp(last, "and") == 0){
        printf("Error: invalid query\n");
        return false;
    }
    if (strcmp(last, "or") == 0){
        printf("Error: invalid query\n");
        return false;
    }
    
    char* prev = queryArray[0];
    char* curr;
    
    // once-over, checking for aa/ao/oa/oo
    for (int i = 1; i < arrayIdx; i++){
        curr = queryArray[i];
        
        if ( ((strcmp(curr, "and") == 0) || (strcmp(curr, "or") == 0)) &&
             ((strcmp(prev, "and") == 0) || (strcmp(prev, "or") == 0)) ) {
            
            printf("Error: invalid query\n");
            return false;
        }
        prev = curr;
    }
    return true;
}


/*
Function: parses queryArray into tree of orPhrases and andPhrases:
    (OrP (AndP word1:ctrs word2:ctrs ...) (AndP word3:ctrs word4:ctrs ...) ...)
Parameters: char** queryArray, array of words from user input
            int arrayIdx, index of first empty slot
            index_t* index, index loaded from indexFile parameter
Returns: set_t* representing the query parsed as described above
*/

set_t* parseQuery(char** queryArray, int arrayIdx, index_t* index)
{
    // set to represent orPhrase (the whole query)
    // only free the sets, not counters (index will do that, as they are not copies)
    set_t* orSet = set_new((void(*)(void *))set_delete);
    
    // set to represent first andPhrase
    set_t* andSet = set_new((void(*)(void *))counters_delete);
    set_insert(orSet, "start", andSet);
    
    char* word;
    char key[MAX_QUERY_LEN/5] = "";
    const char* x = "x";
    
    for (int i = 0; i < arrayIdx; i++){
        word = queryArray[i];

        // signals end of one andPhrase, start of next
        if (strcmp(word, "or") == 0){
            andSet = set_new((void(*)(void *))counters_delete);
            
            strcat(key, x);
            set_insert(orSet, key, andSet);
            continue;
        
        // 'and's are meaningless
        } else if (strcmp(word, "and") == 0){
            continue;
        }
        
        // will == NULL if word DNE in index
        counters_t* ctr = index_find(index, word);
        counters_t* copy = counters_new();
        
        if (ctr == NULL){
            printf("Warning: word '%s' not found in index\n", word);
        } else {
            counters_iterate(ctr, ctrCopy, copy);
        }
        
        set_insert(andSet, word, copy);
    }
    return orSet;
}

/*
Function: format output for the documents that match the query
Parameters: char* queryCopy, a copy of the queryLine
            counters_t* queryScore, the documents' query (overall) scores
            char* directory, the path to the crawler directory
Return: (void)
*/
void output(char* queryCopy, counters_t* queryScore, char* directory)
{
    printf("Query: %s\n", queryCopy);

    counters_t* matchesCounter = counters_new();
    counters_iterate(queryScore, matchCount, matchesCounter);
    int matches = counters_get(matchesCounter, 0);

    if ( matches == 0){
        printf("No documents matched\n\n");
    }
    
    node_t** results = malloc(sizeof(node_t*) * matches);
    for (int i = 0; i < matches; i++){
        results[i] = NULL;
    }
    
    counters_iterate(queryScore, arrayFill, results);

    qsort(results, matches, sizeof(node_t*), sortFunc);
    
    //char* directory = "../data/output";
    
    for (int i = 0; i < matches; i++){

        node_t* current = *(results + i);
        
        int key = current->docID;
        int score = current->score;
        
        char filepath[128];
        sprintf(filepath, "%s%s%d", directory, "/", key);
    
        FILE* fp = fopen(filepath, "r");
        if (fp != NULL){
            char URL[128];
            fgets(URL, sizeof(URL), fp);
            printf("docID %d: score of %d. URL = %s\n", key, score, URL);
            
            fclose(fp);
        }
        free(current);
    }

    free(results);
    counters_delete(matchesCounter);
}

// HELPER FUNCTIONS_____________________________________________________________


// ___ parseQuery() ___

// Called on each node in to-be-copied counters (from index to andSet)
// This was done to allow for clean delete()ing of both index and sets
void ctrCopy(void* ctr, const int key, int count)
{
    counters_set(ctr, key, count);
}


// ___ score() ___

// Called on each andSet during orSet iteration
// Accumulates queryScore as andScores are calculated
void orFunc(void *queryScore, const char *key, void *andSet)  
{
    counters_t* andScore = counters_new();
    
    set_iterate(andSet, maxCtrFunc, andScore);  // MAX andScore
    set_iterate(andSet, andFunc, andScore);     // reduce andScore
    
    // update queryScore w/ each andPhrase's score as they are calculated
    counters_iterate(andScore, addFunc, queryScore);
    counters_delete(andScore);
}

// Called on each counters_t object in andSet (wordCounters)
//      andHelp() makes wordCounter domain match andScore domain
//      leastFunc() takes smaller b/t andScore[key] and ctr[key]
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

// Called on each counterNode of the andScore to be added to queryScore
// Adds documents' andScores to queryScore
void addFunc(void *queryScore, const int key, int count)
{
    int qScore = counters_get(queryScore, key);
    qScore += count;
    counters_set(queryScore, key, qScore);
}

// Sets the contents of andScore as follows:
//      domain(docIDs) = UNION of docIDs in andSet
//      range(counts) = INT_MAX (2147483647)
void maxCtrFunc(void *andScore, const char* key, void* ctr)
{
    counters_iterate(ctr, maxCtrHelper, andScore);
}

void maxCtrHelper(void* andScore, const int key, int count)
{
    counters_set(andScore, key, INT_MAX);
}


// ___ output() ___

// Called on each node of queryScore
// If score > 0 (match), increment matches
void matchCount(void* matchesCounter, const int key, int count)
{
    if (count > 0){
        counters_add(matchesCounter, 0);
    }
}

// Called on each item of queryScore
// fills array with query-matching (docID, score) nodes (score > 0)
void arrayFill(void* array, const int key, int count)
{
    if (count > 0){
        int index = 0;
        node_t** arrayP = (node_t**) array;
        
        while (arrayP[index] != NULL){
            index++;
        }
        
        node_t* new = malloc(sizeof(node_t*));
        new->docID = key;
        new->score = count;
        
        arrayP[index] = new;
    }
}

// Called in qsort(), compares score values of node_t* to be sorted
int sortFunc(const void *a, const void *b)
{
    const node_t* nodeA = *(node_t * const *)a;
    const node_t* nodeB = *(node_t * const *)b;
    
    int aScore = nodeA->score;
    int bScore = nodeB->score;
    
    if (aScore < bScore){
        return 1;
    } else if (aScore > bScore){
        return -1;
    } return 0;
}
