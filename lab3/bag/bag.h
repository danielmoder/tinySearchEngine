#ifndef __BAG_H
#define __BAG_H

#include <stdlib.h>
#include <stdio.h>

typedef struct bag bag_t;

bag_t* bag_new(void (*deleteFunc)(void*) );

void bag_insert(bag_t* bag, void* data);

void* bag_extract(bag_t* bag);

void bag_delete(bag_t* bag);

#endif // __SET_H
