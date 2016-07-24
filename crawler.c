#include <stdlib.h>
#include <stdio.h>
#include "web.h"
#include "lib/bag/bag.h"
#include "lib/set/set.h"
#include "lib/memory/memory.h"


int crawl(char* seedURL){
	bag_t* bag = bag_new(free);
	set_t* beenSearched = set_new(free);

	// Set struct used to keep track of already-searched URLs
	char* toAdd = assertp(malloc(sizeof(char*)), "toAdd messed up...\n");
	toAdd = seedURL;
	set_insert(beenSearched, toAdd, NULL);
	set_delete(beenSearched);

	// // Setting up seedPage
	// WebPage* page = malloc(sizeof(WebPage));
	// page->url = seedURL;
	// page->html = NULL;
	// GetWebPage(page);

	// // Setting up GetNextURL while loop
	// char* HTML = page->html;
	// char* URL = seedURL;
	// int pos = 0;
	// char* result;




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
