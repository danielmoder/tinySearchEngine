//Assumes maxDepth > 0


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "web.h"
#include "lib/bag/bag.h"
#include "lib/set/set.h"
#include "lib/memory/memory.h"

// return true if page is non-NULL and has depth less than maxDepth, else returns false
bool isValid(WebPage* page, int maxDepth)
{
	if ( (page == NULL) || (page->depth > maxDepth) ){
		return false;
	} return true;
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


int crawl(char* seedURL){
	int maxDepth = 1;

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

	char** beenSearched = assertp(malloc(sizeof(char*) * 100), "beenSearched\n");

	char* toAdd = assertp(malloc(strlen(seedURL) + 1), "toAdd\n");
	strcpy(toAdd, seedURL);

	beenSearched[0] = toAdd;

	int index = 1;

	// char* test = "testing\n";
	// toAdd = assertp(malloc(strlen(seedURL) + 1), "toAdd messed up...\n");
	// strcpy(toAdd, test);



	while (rootPage != NULL){
		// Setting up GetNextURL while loop
		char* HTML = rootPage->html;
		char* URL = rootPage->url;
		int depth = rootPage->depth;
		int pos = 0;
		char* result = NULL;

		printf("crawling URL: %s\n\n", URL);

		while ((pos = GetNextURL(HTML, pos, URL, &result)) > 0){
			printf("Found URL: %s\n", result);

			if (! arraySearch(beenSearched, index, result)){

				beenSearched[index] = assertp(malloc(strlen(result) + 1), "beenSearched\n");
				strcpy(beenSearched[index], result);

				WebPage* page = assertp(malloc(sizeof(WebPage)), "new page\n");
				page->url = assertp(malloc(strlen(result) + 1), "new url\n");
				strcpy(page->url, result);

				printf("newPage url = %s, adding to bag\n", page->url);

				page->html = NULL;
				page->depth = depth + 1;
				if (GetWebPage(page)){
					bag_insert(bag, page);
				}

				index++;
			}
			free(result);
		}

		count_free(rootPage->url);
		count_free(rootPage->html);
		count_free(rootPage);
		
	// finding next page to crawl ---- must be non-NULL and have depth <= maxDepth	
		while ((rootPage = bag_extract(bag)) != NULL) {
			printf("\nextracted: %s. Depth = %d\n\n", rootPage->url, rootPage->depth);
			if (rootPage->depth > maxDepth){
				continue;
			}
			break;
		}
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
  char* url = "http://old-www.cs.dartmouth.edu/~cs50/index.html";

	return crawl(url);
}
