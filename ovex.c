#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  StringMap* map = strmap_new();

  char *val;

  map_put(map, "potato", "battery", FREE_NONE);
  if (map_get(map, "potato", (void*) &val)) {
    printf("map[\"potato\"] == %s, len == %zu\n", val, map->size);
  }

  map_put(map, "potato", "carrot", FREE_NONE);
  if (map_get(map, "potato", (void*) &val)) {
    printf("map[\"potato\"] == %s, len == %zu\n", val, map->size);
  }

  map_put(map, "potato", "banana", FREE_NONE);
  if (map_get(map, "potato", (void*) &val)) {
    printf("map[\"potato\"] == %s, len == %zu\n", val, map->size);
  }

  map_put(map, "potato", "orchestra", FREE_NONE);
  if (map_get(map, "potato", (void*) &val)) {
    printf("map[\"potato\"] == %s, len == %zu\n", val, map->size);
  }

  map_free(map);

  return EXIT_SUCCESS;

}
