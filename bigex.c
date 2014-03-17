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

  for(size_t i = 20000; i != 0; --i) {
    map_put(map, (void*) i, (void*) (((uint16_t) -1) - i), FREE_NONE);
  }

  MapIter *iter = mapiter_start(map);
  Pair *pair;

  bool inside = false;

  printf("Size: %zu\n", map->size);

  fputs("{ ", stdout);

  while((pair = mapiter_next(iter))) {

    if (inside) {
      fputs(", ", stdout);
    } else {
      inside = true;
    }
    printf("%zu : %zu", (size_t) pair->key, (size_t) pair->value);

    pair_free(pair);
  }

  puts(" }");

  mapiter_free(iter);
  map_free(map);

  return 0;

}
