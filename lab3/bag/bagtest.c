#include "bag.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
	int intTest = 8;
	int* intP = malloc(sizeof(int));
	memcpy(intP, &intTest, sizeof(int));

	char* stringTest = "abg";
	char** stringP = malloc(sizeof(char*));
	memcpy(stringP, &stringTest, sizeof(char*));


	bag_t* new = bag_new(free);


	bag_insert(new, intP);
	printf("inserting 8\n");
	bag_insert(new, stringP);
	printf("inserting abg\n");


	char** s = bag_extract(new);
	printf("extracting\n");
	int* i = bag_extract(new);
	printf("extracting\n");

	printf("%s (local) == %s (extracted)\n", stringTest, *s);
	printf("%d (local) == %d (extracted)\n", intTest, *i);

	printf("trying to extract again...\n");
	s = bag_extract(new);

	if (s == NULL){
		printf("bag_extract() from empty bag returned NULL\n");
	}

	printf("inserting 8\n");
	printf("inserting abg\n");
	bag_insert(new, intP);
	bag_insert(new, stringP);

	printf("deleting bag\n");
	bag_delete(new);								// no memory leaks, I swear!

	return 0;
}