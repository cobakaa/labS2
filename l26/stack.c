#include "stack.h"

void stack_create(Stack * s) {
    vector_create(&s->data);
    s->size = 0;
}

bool stack_is_empty(const Stack * s) {
    return s->size == 0;
}

void stack_push(Stack * s, SItem item) {
    push_back(&s->data, item);
    s->size++;
}

SItem stack_pop(Stack * s) {
    s->size--;
    SItem item = get_VItem(&s->data, vector_size(&s->data) - 1);
    erase_VItem(&s->data, vector_size(&s->data) - 1);
    return item;
}

void stack_print(const Stack * s) {
    vector_print(&s->data);
}

void stack_destroy(Stack * s) {
    vector_destroy(&s->data);
    s->size = 0;
}

size_t stack_size(const Stack * s) {
    return s->size;
}

Stack * stack_copy(Stack * l, Stack * r) {
    // stack_destroy(l);
    vector_copy(&l->data, &r->data);
    l->size = r->size;
    return l;
}
