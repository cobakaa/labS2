#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char value;
} Item;

typedef struct LItem {
    struct LItem * next;
    Item data;
} LItem;

typedef struct {
    struct LItem * head;
    int size;
    
} List;

typedef struct {
    struct LItem * node;
} Iterator;

bool iterator_equal(const Iterator* lhs, const Iterator* rhs);
Iterator iterator_next(Iterator* i);
Iterator iterator_prev(List * l, Iterator * it);
Item iterator_fetch(const Iterator* i);
void iterator_store(const Iterator* i, const Item t);
Iterator iterator_first(const List* l);
Iterator iterator_last(const List* l);

void list_create(List* l);
Iterator list_insert(List* l, Iterator* i, const Item t);
Iterator list_delete(List* l, Iterator* i);
void list_destroy(List* l);
int list_size(const List* l);
bool list_empty(const List* l);
void list_print(const List* l);

bool list_swap_elements(List * l, int k);

#endif 