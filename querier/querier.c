/*
A search engine query program

Daniel Moder, Summer 2016
*/

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
    while ( fgets(inLine, sizeof(inline), stdin) != NULL){
        printf("%s\n", inLine);
    
    
        // clean
        // parse        (set of 'and' sequence sets -- implied 'or' b/t sets)
        // validDocs    (documents that satisfy the query)
        // rank         (?)
        // output       
    
    }







}


