#if !defined(_MAP_H)
#define _MAP_H

#include "node.h"

typedef struct {
  Node *root;
  uint64_t size;
  comparer cmp;
} Map;

typedef Map StringMap;

typedef struct {
  Map *map;
  void *lastKey;
  bool begin;
} MapIter;

Map* map_new(comparer cmp);
void* map_get(Map *map, void *key);
void map_put(Map *map, void *key, void *value, uint8_t freewhat);
bool map_contains(Map *map, void *key);
bool map_remove(Map *map, void *key);
void map_free(Map *map);

StringMap* strmap_new(void);
extern void* (*strmap_get) (StringMap *map, const char *key);
extern void (*strmap_put)(StringMap *map, const char *key, void *value, uint8_t freewhat);

MapIter* mapiter_start(Map *map);
Pair* mapiter_next(MapIter *iter);
void mapiter_free(MapIter *iter);

#endif
