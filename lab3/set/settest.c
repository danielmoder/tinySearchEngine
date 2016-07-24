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

	printf("*intP = %s\n", *stringP);

	set_insert(newSet, intKey, intP);
	set_insert(newSet, stringKey, stringP);

	char** stringFound;
	int* intFound;

	if ((stringFound = set_find(newSet, stringKey)) != NULL){
		printf("%s\n", *stringFound);
	}

	if ((intFound = set_find(newSet, intKey)) != NULL){
		printf("%d\n", *intFound);
	}

	if (! set_insert(newSet, stringKey, &stringTest)){
		printf("insert returned NULL correctly\n");
	}

	set_delete(newSet);


	return 0;
}