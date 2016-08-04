#include "counters.h"

#include <stdlib.h>
#include <stdio.h>

int main(){


  printf("making new counter\n");
  counters_t* new = counters_new();

  printf("adding to key 4 five times\n");
  counters_add(new, 4);
  counters_add(new, 4);
  counters_add(new, 4);
  counters_add(new, 4);
  counters_add(new, 4);

  printf("adding to key 3 once\n");
  counters_add(new, 3);


  printf("got %d for key 3\n", counters_get(new, 3));
  printf("got %d for key 4\n", counters_get(new, 4));
  printf("got %d for key 555\n", counters_get(new, 555));

  counters_delete(new);
  printf("deleted\n");

  printf("\nmaking new counter\n");
  counters_t* new2 = counters_new();

  printf("adding to key 2 five times\n");
  counters_add(new2, 2);
  counters_add(new2, 2);
  counters_add(new2, 2);
  counters_add(new2, 2);
  counters_add(new2, 2);

  printf("got %d for key 2\n", counters_get(new2, 2));
  printf("got %d for key 555\n", counters_get(new2, 555));

  counters_delete(new2);
  printf("deleted\n");

  return 0;
}
