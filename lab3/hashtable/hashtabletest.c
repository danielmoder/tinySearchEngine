#include "hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){

	int ints[5] = {1, 2, 3, 4, 5};
	char* keys[5] = {"one", "two", "three", "four", "five"};

	int* intPs[5];

	const int slots = 3;
	hashtable_t* hash = hashtable_new(slots, free);

	if (hash == NULL){
		exit(5);
	}

	for (int i = 0; i < 5; i++){
		int* temp = malloc(sizeof(int*));
		intPs[i] = temp;

		memcpy(intPs[i], &ints[i], sizeof(int));
		hashtable_insert(hash, keys[i], intPs[i]);
	}

	for (int i = 0; i < 5; i++){
		int* returned = hashtable_find(hash, keys[i]);
		printf("found %d when searching for key %s\n", *returned, keys[i]);
	}
	
	if (! hashtable_insert(hash, keys[0], intPs[0])){
		printf("insert returned false correctly\n");
	}

	int* notThere = hashtable_find(hash, "notAKey");
	if (notThere == NULL){
		printf("find returned NULL correctly\n");
	}

	hashtable_delete(hash);

	return 0;
}