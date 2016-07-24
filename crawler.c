#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "web.h"
#include "lib/bag/bag.h"
#include "lib/set/set.h"
#include "lib/memory/memory.h"




int crawl(char* seedURL){
	bag_t* bag = bag_new(free);

	char** beenSearched = assertp(malloc(sizeof(char*) * 100), "beenSearched\n");
	int index = 0;

	char* toAdd = assertp(malloc(strlen(seedURL) + 1), "toAdd messed up...\n");
	strcpy(toAdd, seedURL);

	beenSearched[0] = toAdd;


	char* test = "testing\n";
	toAdd = assertp(malloc(strlen(seedURL) + 1), "toAdd messed up...\n");
	strcpy(toAdd, test);
	

	beenSearched[1] = toAdd;

	printf("%s, %s\n", beenSearched[0], beenSearched[1]);

	count_free(beenSearched[0]);
	count_free(beenSearched[1]);
	count_free(beenSearched);




	bag_delete(bag);

	// Setting up seedPage
	WebPage* page = malloc(sizeof(WebPage));
	page->url = seedURL;
	page->html = NULL;
	GetWebPage(page);

	// Setting up GetNextURL while loop
	char* HTML = page->html;
	char* URL = seedURL;
	int pos = 0;
	char* result;

	free(page);


	// while ((pos = GetNextURL(HTML, pos, URL, &result)) > 0){
	// 	printf("Found URL: %s\n", result);

	// 	toAdd
	// 	if (set_insert(beenSearched, ))
	// 	WebPage* page = malloc(sizeof(WebPage));
	// 	page->url = result;
	// 	page->html = NULL;
	// 	GetWebPage(page);

	// 	bag_insert(bag, page);
	// }


	return 0;
}


int main(int argc, char* argv[]){
	return crawl("http://old-www.cs.dartmouth.edu/~cs50/index.html");
}
