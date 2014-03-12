#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int8_t cmp(const void *v1, const void *v2) {

  intptr_t cmv = (intptr_t) v1 - (intptr_t) v2;

  return (int8_t) ((cmv > 0) - (cmv < 0));

}

int main(void) {

  srand(time(NULL));

  Map* map = map_new(cmp);

  intptr_t key, val;
  for(size_t i = 0; i < 20; ++i) {
    key = rand() % 200;
    val = rand() % 100;
    map_put(map, (void*) key, (void*) val, FREE_NONE);
  }

  MapIter *iter = mapiter_start(map);
  Pair *pair;

  bool inside = false;

  printf("Size: %lu\n", map->size);

  fputs("{ ", stdout);

  while((pair = mapiter_next(iter))) {

    if (inside) {
      fputs(", ", stdout);
    } else {
      inside = true;
    }
    printf("%ld : %ld", (uintptr_t) pair->key, (uintptr_t) pair->value);

    pair_free(pair);
  }

  puts(" }");

  mapiter_free(iter);
  map_free(map);

  return 0;

}
