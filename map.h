#if !defined(_MAP_H)
#define _MAP_H

#include "node.h"

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
  Node *root;
  size_t size;
  comparer cmp;
} Map;

typedef Map StringMap;

typedef struct {
  Map *map;
  const void *lastKey;
  bool begin;
} MapIter;

Map* map_new(comparer cmp);
bool map_get(Map *map, const void *key, void **value);
void* map_put(Map *map, const void *key, void *value, uint8_t freewhat);
bool map_contains(Map *map, const void *key);
bool map_remove(Map *map, const void *key);
void map_freeSpec(Map *map, void (*freeKey)(void*), void (*freeVal)(void*));
void map_free(Map *map);

StringMap* strmap_new(void);

MapIter* mapiter_start(Map *map);
Pair* mapiter_next(MapIter *iter);
void mapiter_free(MapIter *iter);

#if defined(__cplusplus)
}
#endif

#endif
