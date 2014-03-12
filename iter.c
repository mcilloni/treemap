#include "map.h"

#include <stdlib.h>

MapIter* mapiter_start(Map *map) {
  MapIter *iter = malloc(sizeof(MapIter));
  iter->map = map;
  iter->lastKey = NULL;
  iter->begin = true;
  return iter;
}

Pair* next(Node *node, const void *lastKey) {

  if (!node) {
    return NULL;
  }

  int8_t cmp = node->cmp(lastKey, node->key);

  //lastKey < node->key
  if (cmp < 0) {
    Pair *pair = next(node->left, lastKey);
    return pair ? pair : node_mkpair(node);
  }

  return next(node->right, lastKey);

}

Pair* mapiter_next(MapIter *iter) {
  Node *root = iter->map->root;

  if (!root) {
    return NULL;
  }

  if(iter->begin) {
    iter->begin = false;
    Pair *pair = node_minpair(root);
    iter->lastKey = pair->key;
    return pair;
  }

  Pair *pair = next(root, iter->lastKey);

  if (pair) {
    iter->lastKey = pair->key;
  }

  return pair;

}

void mapiter_free(MapIter *iter) {
  free(iter);
}
