#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "web.h"
#include "lib/bag/bag.h"
#include "lib/set/set.h"
#include "lib/memory/memory.h"


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
	bag_t* bag = bag_new(free);

	char** beenSearched = assertp(malloc(sizeof(char*) * 100), "beenSearched\n");

	char* toAdd = assertp(malloc(strlen(seedURL) + 1), "toAdd messed up...\n");
	strcpy(toAdd, seedURL);

	beenSearched[0] = toAdd;

	int index = 1;

	// char* test = "testing\n";
	// toAdd = assertp(malloc(strlen(seedURL) + 1), "toAdd messed up...\n");
	// strcpy(toAdd, test);






	// Setting up seedPage
	
	WebPage* page = assertp(malloc(sizeof(WebPage)), "making seedPage\n");
	page->url = seedURL;
	printf("%s\n", seedURL);
	page->html = NULL;
	if (! GetWebPage(page)){ return 99; };

	// Setting up GetNextURL while loop
	char* HTML = page->html;

	count_free(page->html);
	count_free(page);
	
	char* URL = seedURL;
	int pos = 0;
	char* result = NULL;

	

	while ((pos = GetNextURL(HTML, pos, URL, &result)) > 0){
		printf("Found URL: %s\n", result);


		if (! arraySearch(beenSearched, index, result)){
		  //			WebPage* page = assertp(malloc(sizeof(WebPage)), "making a page\n");
		  //	page->url = result;
		  //	page->html = NULL;
		  //	GetWebPage(page);

		  //	bag_insert(bag, page);

			beenSearched[index] = assertp(malloc(strlen(result) + 1), "toAdd messed up...\n");
			strcpy(beenSearched[index], result);
			free(result);
			index++;
		}
	}
	


	

	bag_delete(bag);





	
	printf("%d\n", index);
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
