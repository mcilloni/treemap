#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  StringMap* map = strmap_new();

  strmap_put(map, "potato", "battery", FREE_NONE);
  strmap_put(map, "honey", "poney", FREE_NONE);
  strmap_put(map, "fagiots", "david faggetta", FREE_NONE);
  strmap_put(map, "u fagiots", "lelzie", FREE_NONE);

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
    printf("%s : %s", pair->key, pair->value);

    pair_free(pair);
  }

  puts(" }");

  mapiter_free(iter);
  map_free(map);

  return 0;

}
