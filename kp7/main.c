#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    Matrix m;

    int s, c;
    float elem;
    scanf("%d %d", &s, &c);

    matrix_create(&m, s, c);

    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < c; ++j) {
            scanf("%f", &elem);
            Index ind;
            ind.s = i + 1;
            ind.c = j + 1;
            matrix_add(&m, elem, ind);
        }
    }

    printf("---------\n");

    matrix_print(&m);

    printf("---------\n");

    matrix_inner_print(&m);

    printf("---------\n");

    float value;
    scanf("%f", &value);
    
    Matrix res = matrix_transform(m, value);

    matrix_print(&res);


    return 0;
}