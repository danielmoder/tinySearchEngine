/*
A search engine query program

Daniel Moder, Summer 2016
*/

#include <stdio.h>
#include <string.h>

#include "../common/index.h"


// Declare functions here:


//

int main(int argc, char* argv[])
{
    // Validate arguments
    char* pageDirectory = argv[1];
    char* indexFileName = argv[2];
    
    // Load index from argv
    index_t* index = index_load(indexFileName);

// ASSUMPTION: inLine cannot be greater than 100 characters
//              (this would also solve the array size problem for tokened input)
    
    char inLine[100];
    // read-in loop
    while ( fgets(inLine, sizeof(inLine), stdin) != NULL){
        char* word = strtok(inLine, " ");
        
        printf("%s\n", word);
        
        while ( (word = strtok(NULL, " ")) != NULL){
            printf("%s\n", word);
        }
        
    
        // clean
        // parse        (set of 'and' sequence sets -- implied 'or' b/t sets)
        // validDocs    (documents that satisfy the query)
        // rank         (?)
        // output       
    
    }







}


