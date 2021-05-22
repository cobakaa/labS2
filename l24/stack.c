#include "stack.h"
#include <stdlib.h>

void stack_create(Stack * s) {
    s->top = 0;
    s->size = 0;
}

bool stack_empty(const Stack * s) {
    return s->size == 0;
}

int stack_size(const Stack * s) {
    return s->size;
}

bool stack_push(Stack * s, char c) {
    struct Item * i = (struct Item*)malloc(sizeof(struct Item));

    if (!i) {
        return false;
    }

    i->data = c;
    i->prev = s->top;
    s->top = i;
    s->size++;
    return true;
}

bool stack_pop(Stack * s) {
    if (s->size == 0) {
        return false;
    }

    struct Item* i = s->top;
    s->top = s->top->prev;
    s->size--;
    free(i);
    return true;
}

char stack_top(const Stack * s) {
    if (s->top) {
        return s->top->data;
    }
    return '\0';
}

void stack_destroy(Stack * s) {
    while (s->top) {
        struct Item* i = s->top;
        s->top = s->top->prev;
        free(i);
    }
    s->top = 0;
    s->size = 0;
}