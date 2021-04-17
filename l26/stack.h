#ifndef __STACK_H__
#define __STACK_H__

#include "vector.h"

typedef VItem SItem;

typedef struct 
{
    Vector data;
    size_t size;

} Stack;


void stack_create(Stack * s);
bool stack_is_empty(const Stack * s);
void stack_push(Stack * s, SItem item);
SItem stack_pop(Stack * s);
void stack_print(const Stack * s);
void stack_destroy(Stack * s);
size_t stack_size(const Stack * s);
Stack * stack_copy(Stack * l, Stack * r);


#endif