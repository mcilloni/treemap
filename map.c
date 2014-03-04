#include "map.h"

#include <string.h>

#include <jemalloc/jemalloc.h>

Map* map_new(comparer cmp) {
  Map *map = calloc(1, sizeof(Map));
  map->cmp = cmp;
  return map;
}

void* map_get(Map *map, void *key) {
  if (!map->root) {
    return NULL;
  }

  return node_get(map->root,key);
}

void map_put(Map *map, void *key, void *value, uint8_t freewhat) {
  map->root = node_add(map->root, key, value, map->cmp, freewhat);
  map->root->color = BLACK;
  ++(map->size);
}

bool map_contains(Map *map, void *key) {
  return (bool) map_get(map, key);
}

bool map_remove(Map *map, void *key) {
	bool ret = false;
	map->root = node_delete(map->root, key, &ret);
	map->root->color = BLACK;

	if (ret) {
		--(map->size);
    }

	return ret;
}

void map_free(Map *map, bool free_entries) {
  node_free(map->root);
  free(map);
}

int8_t strcomparer(void* s1, void* s2) {
  int comp = strcmp(s1, s2);

  return (int8_t) (comp > 0) - (comp < 0);
}

StringMap* strmap_new(void) {
  return map_new(strcomparer);
}
