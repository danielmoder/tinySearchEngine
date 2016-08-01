#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct counters counters_t;

counters_t* counters_new(void);

void counters_add(counters_t* ctrs, int key);

int counters_get(counters_t* ctrs, int key);

void counters_delete(counters_t* ctrs);

void counters_set(counters_t *ctrs, int key, int count);

void counters_iterate(counters_t *ctrs,
		      void (*itemfunc)(void *arg, const int key, int count),
		      void *arg);

#endif //__COUNTERS_H
