#ifndef __TREE_H__
#define __TREE_H__

#include <stdlib.h>
#include "token.h"
#include "vector.h"

typedef struct Tree {
    Token node;
    struct Tree * left;
    struct Tree * right;
} Tree;

void tree_create(struct Tree **node, Vector * postf);
void tree_print(struct Tree * t, size_t depth);
void tree_infix(struct Tree * t);
void tree_transform(struct Tree ** t);

#endif

