#ifndef __BAG_H
#define __BAG_H

#include <stdlib.h>
#include <stdio.h>

typedef struct bag bag_t;

bag_t* bag_new(void (*deleteFunc)(void*) );

void bag_insert(bag_t* bag, void* data);

void* bag_extract(bag_t* bag);

void bag_delete(bag_t* bag);


/* Set value of the counter indicated by key.
 * If the key does not yet exist, create a counter for it
 * and initialize its counter value to 'count'.
 * NULL counters is ignored.
 */
void counters_set(counters_t *ctrs, int key, int count);

/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 */
void counters_iterate(counters_t *ctrs,
		      void (*itemfunc)(void *arg, const int key, int count),
		      void *arg);

#endif // __SET_H
