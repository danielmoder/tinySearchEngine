#ifndef __SET_H
#define __SET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct set set_t;

set_t* set_new(void (*destructor)(void*) );

void* set_find(set_t* set, char* key);

bool set_insert(set_t* set, char* key, void* data);

void set_delete(set_t* set);

#endif // __SET_H
