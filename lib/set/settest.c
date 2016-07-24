#include "set.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
	set_t* newSet = set_new(free);

	int intTest = 99;
	int* intP = malloc(sizeof(int));
	memcpy(intP, &intTest, sizeof(int));

	char* intKey = "ninety-nine";


	char* stringTest = "abcdefghi";
	char** stringP = malloc(sizeof(char*));
	memcpy(stringP, &stringTest, sizeof(char*));

	char* stringKey = "alphabet part";

	printf("inserting int %d with key '%s'\n", intTest, intKey);
	set_insert(newSet, intKey, intP);
	printf("inserting string '%s' with key '%s'\n", stringTest, stringKey);
	set_insert(newSet, stringKey, stringP);

	char** stringFound;
	int* intFound;

	if ((stringFound = set_find(newSet, stringKey)) != NULL){
	  printf("found '%s' searching for key '%s'\n", *stringFound, stringKey);
	}

	if ((intFound = set_find(newSet, intKey)) != NULL){
	  printf("found %d searching for key '%s'\n", *intFound, intKey);
	}

	if (! set_insert(newSet, stringKey, &stringTest)){
		printf("insert returned NULL correctly\n");
	}

	printf("deleting set\n");
	set_delete(newSet);


	return 0;
}
