#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

void vector_create(Vector * vector) {
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;

    // return *vector;
}

Vector * push_back(Vector * vector, VItem item) {
    if (vector->data == NULL) {
        vector->size = 0;
        vector->capacity = 1;
        vector->data = (VItem*)malloc(vector->capacity * sizeof(VItem));
        //return vector;
    } else {
        if (vector->size + 1 > vector->capacity) {
            vector->capacity *= 2;
            VItem * tmp;
            tmp = (VItem*)realloc(vector->data, vector->capacity * sizeof(VItem));
            if (tmp != NULL) {
                vector->data = tmp;
            } else {
                free(vector->data);
                printf("No memory.");
                exit(1);      
            }
        }
    }

    vector->size++;
    vector->data[vector->size - 1] = item;

    return vector;
}

VItem get_VItem(const Vector * vector, int ind) {
    return vector->data[ind];
}

void vector_destroy(Vector * vector) {
    free(vector->data);
    vector->size = 0;
    vector->capacity = 0;
}

void set_VItem(Vector * vector, int ind, VItem value) {
    vector->data[ind] = value;
}

void erase_VItem(Vector * vector, int ind) {
    for (int i = ind + 1; i < vector->size; ++i) {
        vector->data[i - 1] = vector->data[i];
    }
    vector->size--;
}

void vector_shrink_to_fit(Vector * vector) {
    if (vector->capacity > vector->size) {
        vector->data = (VItem*)realloc(vector->data, vector->size * sizeof(VItem));
        vector->capacity = vector->size;
    }
}

bool vector_is_empty(const Vector * vector) {
    return vector->data == NULL;
}

void vector_print(const Vector * vector) {
    for (int i = vector->size - 1; i >= 0; --i) {
        printf(" ");
        printf("%c\n", get_VItem(vector, i).data.value);
    }
    printf("\n");
}


size_t vector_size(const Vector * vector) {
    return vector->size;
}

Vector * vector_copy(Vector * l, Vector * r) {
    for (int i = 0; i < (vector_size(l) < vector_size(r) ? vector_size(l) : vector_size(r)); ++i) {
        l->data[i] = r->data[i];
    }

    if (vector_size(l) < vector_size(r)) {
        for (int i = vector_size(l); i < vector_size(r); ++i) {
            push_back(l, r->data[i]);
        }
    } else {
        l->size = r->size;
    }

    vector_destroy(r);
    return l;
}