#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct counters counters_t;

counters_t* counters_new(void);

void counters_add(counters_t* ctrs, int key);

int counters_get(counters_t* ctrs, int key);

void counters_delete(counters_t* ctrs);

#endif //__COUNTERS_H
