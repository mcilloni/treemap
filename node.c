#include "node.h"

#include <stdlib.h>

Node* node_new(const void *key, void *val, comparer cmp, uint8_t freewhat) {
  Node *ret = calloc(1, sizeof(Node));
  ret->key = key;
  ret->value = val;
  ret->color = RED;
  ret->cmp = cmp;
  ret->freewhat = freewhat;
  return ret;
}

Node* node_add(Node* node, const void *keyV, void *value, comparer cmp, uint8_t freewhat, void **oldvalue) {

  if (!node) {
    *oldvalue = NULL;
    return node_new(keyV, value, cmp, freewhat);
  }

  switch(node->cmp(keyV,node->key)) {
  case 1:
    node->right = node_add(node->right, keyV, value, node->cmp, freewhat, oldvalue);
	break;

  case -1:
	node->left = node_add(node->left, keyV, value, node->cmp, freewhat, oldvalue);
	break;

  default:
  *oldvalue = node->value;
	node->value = value;
	break;		
  }

  return node_fixUp(node);

}

Node* node_rotateLeft(Node *node) {
  Node *ret = node->right;
  node->right = ret->left;
  ret->left = node;
  ret->color = ret->left->color;
  ret->left->color = RED;
  return ret;
}

Node* node_rotateRight(Node *node) {
  Node *ret = node->left;
  node->left = ret->right;
  ret->right = node;
  ret->color = ret->right->color;
  ret->right->color = RED;
  return ret;
}

void node_colorFlip(Node *node) {
  node->color = !(node->color);
  node->left->color = !(node->left->color);
  node->right->color = !(node->right->color);
}

bool node_isRed(Node *node) {
  return node && node->color;
}

bool node_isBlack(Node *node) {
  return !node || !(node->color);
}

void node_free(Node *node, void (*freeKey)(void*), void (*freeVal)(void*)) {

  if(!node) {
    return;
  }

  node_free(node->left, freeKey, freeVal);
  node_free(node->right, freeKey, freeVal);

  if (node->freewhat & FREE_KEY) {
    if(node->key) {
      freeKey((void*) node->key);
    }
  }

  if (node->freewhat & FREE_VALUE) {
    if(node->value) {
      freeVal(node->value);
    }
  }

  free(node);

}

Node* node_fixUp(Node *node) {
  if (node_isRed(node->right)) {
	node = node_rotateLeft(node);
  }
  
  if (node_isRed(node->left) && node_isRed(node->left->left)) {
	node = node_rotateRight(node);
	node_colorFlip(node);
  }
  
  return node;
}

Node* node_moveRedLeft(Node *node) {

  node_colorFlip(node);

  if (node_isRed(node->right->left)) { 
    node->right = node_rotateRight(node->right);
	node = node_rotateLeft(node);
	node_colorFlip(node);
  }

  return node;

}

Node* node_moveRedRight(Node *node) {

  node_colorFlip(node);

  if (node_isRed(node->left->left)) { 
	node = node_rotateRight(node);
	node_colorFlip(node);
  }

  return node;

}

bool node_get(Node *node, const void *keyV, void **valueV) {

  if(!node) {
    return false;
  }

  switch (node->cmp(keyV, node->key)) {
  case 0: {
    *valueV = node->value;
    return true;
  }
  case -1:
	return node_get(node->left, keyV, valueV);
  default:
	return node_get(node->right, keyV, valueV);
  }
  return false;
}

Node* node_deleteMin(Node *node) { 
  if (!node->left) {
    return NULL;
  }

  if (node_isBlack(node->left) && node_isBlack(node->left->left)) {
    node= node_moveRedLeft(node);
  }

  node->left = node_deleteMin(node->left);
  return node_fixUp(node);
}

Pair* node_mkpair(Node *node) {
  if (!node) {
    return NULL;
  }

  Pair *ret = malloc(sizeof(Pair));
  ret->key = node->key;
  ret->value = node->value;
  return ret;
}

Pair* node_minpair(Node *node) {
  if(!node->left) {
    return node_mkpair(node);
  } else {
    return node_minpair(node->left);
  }  
}

void* node_min(Node *node) {
  if(!node->left) {
    return (void*) node->key;
  } else {
    return node_min(node->left);
  }
}

Node* node_delete(Node *node, const void *keyV, bool *found) { 

  if (node->cmp(keyV,node->key)) {
    if (node_isRed(node->left) && node_isRed(node->left->left)) {
      node = node_moveRedLeft(node);
    }
    node->left = node_delete(node->left, keyV, found);
  } else {

    if (node_isRed(node->left)) {
      node = node_rotateRight(node);
    }

    if (!node->cmp(keyV, node->key) && !(node->right)) {
      *found = true;
      return NULL;
    }

    if (node_isBlack(node->right) && node_isBlack(node->right->left)) {
      node = node_moveRedRight(node);
    }

    if (node->cmp(keyV, node->key)) {
      node_get(node->right, node_min(node->right), &(node->value));
      node->key = node_min(node->right);
      node->right = node_deleteMin(node->right);
      *found = true;
    } else {
      node->right = node_delete(node->right, keyV, found);
    }

  } 

  return node_fixUp(node);

}

void pair_free(Pair *pair) {
  free(pair);
}
