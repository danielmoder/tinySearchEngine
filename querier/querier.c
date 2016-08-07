/*
A search engine query program

Daniel Moder, Summer 2016
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../common/index.h"
#include "../lib/hashtable/hashtable.h"
#include "../lib/set/set.h"
#include "../lib/counters/counters.h"



// Declare functions here:
int cleanQuery(char* queryLine, char** queryArray); 
            // will return number of items in array

set_t* parseQuery(char** queryArray, int numWords);

//

int main(int argc, char* argv[])
{
    // Validate arguments
    // char* pageDirectory = argv[1];
    // char* indexFileName = argv[2];
    
    // Load index from argv
    // index_t* index = index_load(indexFileName);

// ASSUMPTION: inLine cannot be greater than 100 characters
//              (this would also solve the array size problem for tokened input)
    
    char queryLine[100];
    // read-in loop
    while ( fgets(queryLine, sizeof(queryLine), stdin) != NULL){
        const int arraySize = 50;
        char* queryArray[arraySize];
        
// CLEAN ________________________________________
        int arrayIdx = 0;
        char* word = strtok(queryLine, " ");
        
        while ( word != NULL){ // get all words in query
        
            int i = 0;
            while ( (word[i] != '\0') && (word[i] != '\n') ){
            
                word[i] = tolower(word[i]);
                
                if (word[i] < 'a' || word[i] > 'z'){
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
// endCLEAN ________________________________________


// PARSE ________________________________________
        char* prev = queryArray[0];
        char* curr;
        
        //set_t* querySet = set_new(free);    // destructor will really be something like
                                            // set_iterate(counters_delete), free(set)



        // check for leading/trailing and/or
        
        char* last = queryArray[(arrayIdx-1)];
        printf("%s\n", last);
        if ( (strcmp(prev, "and") == 0) || (strcmp(prev, "or") == 0) || (strcmp(last, "and") == 0) || (strcmp(last, "or") == 0) ) {
             
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
        
        

        // parse        (set of 'and' sequence sets -- implied 'or' b/t sets)
        // validDocs    (documents that satisfy the query)
        // rank         (?)
        // output       
    
    }







}


