//Assumes maxDepth > 0

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

inline static void logr(const char *word, const int depth, const char *url)
{
  printf("%2d %*s%9s: %s\n", depth, depth, "", word, url);
}


//returns true if array DOES contain the given key
bool arraySearch (char** array, int index, char* key)
{
	for (int i = 0; i < index; i++){
		if ((strcmp(array[i], key) == 0)){
			return true;
		}
	}
	return false;
}

void toFile(char* path, WebPage* web, int fileID)
{
  char filename[strlen(path)+5];
  sprintf(filename, "%s/%d", path, fileID);
  
  FILE* fp = NULL;
  if ( (fp = fopen(filename, "w")) == NULL){
    logr("FAILED", depth, result);
    return;
  }
  
  fprintf(fp, "%s\n%d\n%s\n", web->url, web->depth, web->html);
  fclose(fp);
}

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

int crawl(char* seedURL, char* directory, int maxDepth)
{
	// Setting up seedPage
	WebPage* rootPage = assertp(malloc(sizeof(WebPage)), "making seedPage\n");

	rootPage->url = assertp(malloc(strlen(seedURL) + 1), "new URL\n");
	strcpy(rootPage->url, seedURL);

	rootPage->html = NULL;
	rootPage->depth = 0;
	if (! GetWebPage(rootPage)){
		return 2;
	}

	bag_t* bag = bag_new(free);

	char** beenSearched = assertp(malloc(sizeof(char*) * 1000), "beenSearched\n");

	beenSearched[0] = assertp(malloc(strlen(seedURL) + 1), "toAdd\n");
	strcpy(beenSearched[0], seedURL);

	int fileID = 0;
	int index = 1;


	while (rootPage != NULL){
		// Setting up GetNextURL while loop
		char* HTML = rootPage->html;
		char* URL = rootPage->url;
		int depth = rootPage->depth;
		int pos = 0;
		char* result = NULL;
		
	    logr("Fetched", depth, URL);

		toFile(directory, rootPage, fileID++);
		logr("Saved", depth, URL);

		while ((pos = GetNextURL(HTML, pos, URL, &result)) > 0){
		  if (depth >= maxDepth){
		    free(result);
		    break;
		  }

		  if ( (! arraySearch(beenSearched, index, result)) && (IsInternalURL(result)) && (NormalizeURL(result) ) ) {
            logr("Added", depth, result);
            
			beenSearched[index] = assertp(malloc(strlen(result) + 1), "beenSearched\n");
			strcpy(beenSearched[index], result);
			index++;

			WebPage* page = assertp(malloc(sizeof(WebPage)), "new page\n");
			page->url = assertp(malloc(strlen(result) + 1), "new url\n");
			strcpy(page->url, result);

			page->html = NULL;
			page->depth = depth + 1;

			if (GetWebPage(page)){
				bag_insert(bag, page);
			} else {
			    logr("FAILED", depth, result);
				webDelete(page);
			}
		  }
		  
            if (! IsInternalURL(result)){
                logr("EXTERNAL", depth, result);
            }
                
			free(result);
		}

		webDelete(rootPage);

		rootPage = bag_extract(bag);
	}

	// clean up bag

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
    
    int MAX_DEPTH = 2;
    char* depth = argv[3];
    if (! isdigit(depth[0]) ){
        printf("Error: depth must be an integer\n");
        return 1;
    } else if ( (atoi(depth) < 0) || (atoi(depth) > MAX_DEPTH) ){
        printf("Error: depth must be between %d and 0\n", MAX_DEPTH);
        return 1;
    }
    
    crawl(seedURL, directory, atoi(depth));
	
    return 0;
}
