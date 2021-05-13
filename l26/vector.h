#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>
#include <stdbool.h>

// typedef int VItem;

typedef struct
{
    int key;
    char value[32];
} VItem;


typedef struct {
    VItem * data;
    size_t size;
    size_t capacity;
} Vector;

void vector_create(Vector * vector);
Vector * push_back(Vector * vector, VItem item);
VItem get_VItem(const Vector * vector, int ind);
void set_VItem(Vector * vector, int ind, VItem value);
void vector_destroy(Vector * vector);
void erase_VItem(Vector * vector, int ind);
void vector_shrink_to_fit(Vector * vector);
bool vector_is_empty(const Vector * vector);
void vector_print(const Vector * vector);
size_t vector_size(const Vector * vector);
Vector * vector_copy(Vector * l, Vector * r);

#endif