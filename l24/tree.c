#include "tree.h"
#include <stdio.h>
#include <string.h>

struct Tree *tree_node_create(Token *token)
{
    struct Tree *node = (struct Tree *)malloc(sizeof(struct Tree));

    node->node = *token;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void tree_create(struct Tree **node, Vector * postf) {
    Token token;

    if (!vector_is_empty(postf)) {
        VItem tmp = vector_back(postf);
        // token.type = tmp.type;
        
        if (tmp.item.type == OPERATOR || tmp.item.type == UNARY_OPERATOR) {
            token = tmp.item;
        } else if (sscanf(tmp.item.data.variable_name, "%f", &token.data.value_float) == 1) {
            token.type = FLOAT;
        } else {
            token.type = VARIABLE;
            strcpy(token.data.variable_name, tmp.item.data.variable_name);
        }

        pop_back(postf);
        (*node) = tree_node_create(&token);

        if (token.type == OPERATOR || token.type == UNARY_OPERATOR) {
            tree_create(&(*node)->right, postf);

            if (token.type == OPERATOR) {
                tree_create(&(*node)->left, postf);
            }
        }

    }
}

void tree_infix(struct Tree * t)
{
    if (t != NULL) {
        if ((t->left && t->right) || t->node.type == UNARY_OPERATOR)
            printf("(");

        tree_infix(t->left);
        token_print(&(t->node));
        tree_infix(t->right);

        if ((t->right && t->left) || t->node.type == UNARY_OPERATOR)
            printf(")");
    }
}

void tree_print(struct Tree * t, size_t depth)
{
    if (t != NULL) {
        for (int i = 0; i < depth; ++i) {
            printf("\t");
        }
        token_print(&(t->node)); printf("\n");
        tree_print(t->left,  depth + 1);
        tree_print(t->right, depth + 1);
    }
}

bool is_unary_operator(Token t) {
    return t.type == UNARY_OPERATOR;
}

bool minus_clear(struct Tree ** t) {
    Tree * tmp = *t;
    Tree * tmp1;
    // Tree * tmp2;

    if (is_unary_operator(tmp->node) && is_unary_operator(tmp->right->node)) {
        tmp1 = tmp->right->right;
        *t = tmp1;
        return true;
    }
    return false;
}

void subtree_transform(struct Tree ** t) {

    Tree * tmp = *t;

    if (!tmp) {
        return;
    }

    Tree * tmp1;
    Tree * tmp2;
    if (tmp->right && is_unary_operator(tmp->right->node) && tmp->node.type == OPERATOR && tmp->node.data.operator_name == '*') {
        tmp1 = tmp->right;
        tmp2 = tmp;
        tmp2->right = tmp->right->right;
        tmp1->right = tmp2;
        *t = tmp1;
        return;
    }

    // tmp = *t;

    if (tmp->left && is_unary_operator(tmp->left->node) && tmp->node.type == OPERATOR && tmp->node.data.operator_name == '*') {
        tmp1 = tmp->left;
        tmp2 = tmp;
        tmp2->left = tmp->left->right;
        tmp1->right = tmp2;
        *t = tmp1;
        return;
    }

}

void tree_transform(struct Tree ** t) {
    Tree * tmp = *t;
    if (!tmp) {
        return;
    }

    subtree_transform(t);
    tree_transform(&(*t)->right);
    // subtree_transform(t);
    tree_transform(&(*t)->left);
    subtree_transform(t);
    while (minus_clear(t)) {};
}