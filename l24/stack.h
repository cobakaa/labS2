#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

struct Item {
    char data;
    struct Item * prev;
};

typedef struct {
    struct Item * top;
    int size;

} Stack;

void stack_create(Stack * s);
bool stack_empty(const Stack * s);
int stack_size(const Stack * s);
bool stack_push(Stack * s, char c);
bool stack_pop(Stack * s);
char stack_top(const Stack * s);
void stack_destroy(Stack * s);

#endif