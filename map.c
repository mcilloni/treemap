#include "map.h"

#include <stdlib.h>
#include <string.h>

Map* map_new(comparer cmp) {
  Map *map = calloc(1, sizeof(Map));
  map->cmp = cmp;
  return map;
}

bool map_get(Map *map, const void *key, void **value) {
  if (!map->root) {
    return false;
  }

  return node_get(map->root,key, value);
}

void* map_put(Map *map, const void *key, void *value, uint8_t freewhat) {
  void* oldvalue;
  map->root = node_add(map->root, key, value, map->cmp, freewhat, &oldvalue);
  map->root->color = BLACK;
  map->size += (oldvalue == NULL);
  return oldvalue;
}

bool map_contains(Map *map, const void *key) {
  void *value;
  return (bool) map_get(map, key, &value);
}

bool map_remove(Map *map, const void *key) {
	bool ret = false;
	map->root = node_delete(map->root, key, &ret);
	map->root->color = BLACK;

	if (ret) {
		--(map->size);
    }

	return ret;
}

void map_freeSpec(Map *map, void (*freeKey)(void*), void (*freeVal)(void*)) {
  if (!map) {
    return;
  }

  if (!freeKey) {
    freeKey = free;
  }

  if (!freeVal) {
    freeVal = free;
  }

  node_free(map->root, freeKey, freeVal);
  free(map);
}

void map_free(Map *map) {
  map_freeSpec(map, NULL, NULL);
}

int8_t strcomparer(const void* s1, const void* s2) {
  int comp = strcmp(s1, s2);

  return (int8_t) (comp > 0) - (comp < 0);
}

StringMap* strmap_new(void) {
  return map_new(strcomparer);
}

