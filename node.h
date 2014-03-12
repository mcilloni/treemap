#if !defined(_NODE_H)
#define _NODE_H

#include <stdbool.h>
#include <stdint.h>

static const bool BLACK = false, RED = true;

typedef int8_t (*comparer)(const void*,const void*);

typedef struct {
  const void *key;
  void *value;
} Pair;

enum freemap {                                                                                                                     
    FREE_NONE = 0,                                                                                                                
    FREE_KEY = 1,       
    FREE_VALUE = 10                                                                                                            
};

typedef struct node_s {
  struct node_s *left, *right;
  const void *key;
  void *value;
  bool color; //RED = true, black = false
  uint8_t freewhat;
  comparer cmp;
} Node;

Node* node_new(const void *key, void *val, comparer cmp, uint8_t freewhat);
Node* node_add(Node* node, const void *keyV, void *value, comparer cmp, uint8_t freewhat, bool *newkey);
Node* node_rotateLeft(Node *node);
Node* node_rotateRight(Node *node);
void node_colorFlip(Node *node);
bool node_isRed(Node *node);
bool node_isBlack(Node *node);
void node_free(Node *node);
Node* node_fixUp(Node *node);
Node* node_moveRedLeft(Node *node);
Node* node_moveRedRight(Node *node);
bool node_get(Node *node, const void *keyV, void **valueV);
Pair* node_mkpair(Node *node);
Node* node_deleteMin(Node *node); 
void* node_min(Node *node);
Pair* node_minpair(Node *node);
Node* node_delete(Node *node, const void *keyV, bool *found); 

void pair_free(Pair *pair);

#endif
