/*
A search engine query program

Daniel Moder, Summer 2016
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../common/index.h"


// Declare functions here:


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
    
    char inLine[100];
    // read-in loop
    while ( fgets(inLine, sizeof(inLine), stdin) != NULL){
        char* word = strtok(inLine, " ");
        
        while ( (word = strtok(NULL, " ")) != NULL){ // get all words in query
        
            int i = 0;
            while ( (word[i] != '\0') || (word[i] != '\n') ){
            
                word[i] = tolower(word[i]);
                
                if (word[i] < 'a' || word[i] > 'z'){
                    printf("Error: invalid character %c\n", word[i]);
                    return 1;
                }
                i++;
            }
            printf("%s\n", word);
        }
        
    
        // clean
        // parse        (set of 'and' sequence sets -- implied 'or' b/t sets)
        // validDocs    (documents that satisfy the query)
        // rank         (?)
        // output       
    
    }







}


