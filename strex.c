#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  StringMap* map = strmap_new();

  map_put(map, "potato", "battery", FREE_NONE);
  map_put(map, "honey", "poney", FREE_NONE);
  map_put(map, "flare", "guaxxa", FREE_NONE);
  map_put(map, "guagua", "lelzie", FREE_NONE);

  void *val;

  if (map_get(map, "flare", &val)) {
    puts(val);
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
    printf("%s : %s", (char*) pair->key, (char*) pair->value);

    pair_free(pair);
  }

  puts(" }");

  mapiter_free(iter);
  map_free(map);

  return 0;

}
