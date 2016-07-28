/*
crawler.c       Daniel Moder        July, 2016
This file contains source for a web crawler. It includes functions:
    logr: formats and prints messages to track progress
    arraySearch
    toFile: writes HTML to a file in the specified directory
    webDelete: deletes a WebPage object
    crawl
*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "web.h"
#include "lib/bag/bag.h"
#include "lib/set/set.h"
#include "lib/memory/memory.h"

/*
Function: format and print messages to track changes
Parameters: const char* word, the action word to be printed with the message
            const int depth, the depth of the current crawl
            const char *url, the target url
Returns: (void)
*/

inline static void logr(const char* word, const int depth, const char *url)
{
  printf("- %2d %*s%9s: %s\n", depth, depth, "", word, url);
}


/*
Function: Determines if a string is in an array of strings
Parameters: char** array, the array to be searched
            int index, the first free slot in the array
            char* key, the string to be searched for
Returns: true if the array contains the key, else false
*/

bool arraySearch (char** array, int index, char* key)
{
	for (int i = 0; i < index; i++){
		if ((strcmp(array[i], key) == 0)){
			return true;
		}
	}
	return false;
}


/*
Function: write the html of a webpage to a file in a given directory
Parameters: char* path, the path of the directory to write into
            WebPage* web, the target WebPage object
            int fileID, the name of the file to be written
Returns: (void)
*/

void toFile(char* path, WebPage* web, int fileID)
{
  char filename[strlen(path)+6]; // 4 digit max for fileID (*** assumption)
  sprintf(filename, "%s/%d", path, fileID);
  
  FILE* fp = NULL;
  if ( (fp = fopen(filename, "w")) == NULL){
    logr("FAILED", web->depth, web->url);
    return;
  }
  
  fprintf(fp, "%s\n%d\n%s\n", web->url, web->depth, web->html);
  fclose(fp);
}


/*
Function: free a WebPage object and its contents
Parameters: WebPage* web
Returns: (void)
Assumptions: web, web->url, and web->html must have been allocated
                (or GetWebPage must have been called, allocating html)            
*/

void webDelete(WebPage* web)
{
    if (web != NULL){
        if (web->url != NULL){
            count_free(web->url);
        }
        if (web->html != NULL){
            count_free(web->html);
        }
        count_free(web);
    }
}



WebPage* pageNew(char* url, int depth)
{
    WebPage* newPage = assertp(malloc(sizeof(WebPage)), "newPage\n");
    newPage->url = assertp(malloc(strlen(url) + 1), "newURL\n");
    strncpy(newPage->url, url, strlen(url) + 1);
    
    newPage->html = NULL;
    newPage->depth = depth;
    
    return newPage;
}



/*
Function: crawl pages starting from seedURL to a specified depth, and write
            html to directory
Parameters: char* seedURL, the url from which to start the crawl
            char* directory, the directory into which to write the html files
            int maxDepth, the max depth to crawl
Returns: 0 upon success, 1 if seedURL is not accessible 
*/

int crawl(char* seedURL, char* directory, int maxDepth)
{
	// seedPage
	WebPage* rootPage = pageNew(seedURL, 0);

    // bag
	bag_t* bag = bag_new(free);
	bag_insert(bag, rootPage);

    // array
	char** beenSearched = assertp(malloc(sizeof(char*) * 1000), "array\n");
	beenSearched[0] = assertp(malloc(strlen(seedURL) + 1), "toAdd\n");
	strcpy(beenSearched[0], seedURL);

	int fileID = 0;
	int index = 1;

	while ((rootPage = bag_extract(bag)) != NULL){
	
	    if (! GetWebPage(rootPage)){
		    logr("FAILED", rootPage->depth, rootPage->url);
			webDelete(rootPage);
			continue;
		}
		logr("Fetched", rootPage->depth, rootPage->url);
		
		char* HTML = rootPage->html;
		char* URL = rootPage->url;
		int depth = rootPage->depth;
		


		toFile(directory, rootPage, fileID++);
		logr("Saved", depth, URL);
		
		if (depth >= maxDepth){
		    webDelete(rootPage);
		    continue;
		}
		
		int pos = 0;
		char* result = NULL;
		
		while ((pos = GetNextURL(HTML, pos, URL, &result)) > 0){
		  if (depth >= maxDepth){
		    free(result);
		    break;
		  }
		  
		  if ( (! arraySearch(beenSearched, index, result)) && \
		        (IsInternalURL(result)) && (NormalizeURL(result) ) ) {
		        
            logr("Added", depth, result);
            
			beenSearched[index] = assertp(malloc(strlen(result) + 1), "url\n");
			strcpy(beenSearched[index], result);
			index++;
            
			WebPage* page = pageNew(result, depth+1);

			bag_insert(bag, page);
          }
            
            if (! IsInternalURL(result)){
                logr("EXTERNAL", depth, result);
            }
                
			free(result);
		}

		webDelete(rootPage);
	}

	bag_delete(bag);

    
	// clean up array
	for (int i = 0; i < index; i++){
		count_free(beenSearched[i]);
	}
	count_free(beenSearched);
	return 0;
}



int main(int argc, char* argv[]){

    // Parse arguments
    if (argc != 4){
        printf("Error: crawler must receive exactly three arguments\n");
        return 1;
    }
    
    char* seedURL = argv[1];
    if ( !( (IsInternalURL(seedURL)) && (NormalizeURL(seedURL)) )){
        printf("Error: invalid seedURL\n");
        return 1;
    }
    
    char* directory = argv[2];
    if ( (access (directory, W_OK)) == -1){
        printf("Error: cannot write to directory %s\n", directory);
        return 1;
    }
    
    int MAX_DEPTH = 3;
    char* depth = argv[3];
    if (! isdigit(depth[0]) ){
        printf("Error: depth must be an integer\n");
        return 1;
    } else if ( (atoi(depth) < 0) || (atoi(depth) > MAX_DEPTH) ){
        printf("Error: depth must be between %d and 0\n", MAX_DEPTH);
        return 1;
    }
    
    if (crawl(seedURL, directory, atoi(depth)) == 1){
        return 1;
    }
    
    return 0;
}
