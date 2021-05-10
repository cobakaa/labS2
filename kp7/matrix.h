#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdbool.h> 

#define MAX_SIZE 100

typedef struct
{
    int CIP[MAX_SIZE + 1];
    int PI[MAX_SIZE];
    float YE[MAX_SIZE];
    int K, N, M;
} Matrix;

typedef struct {
    int s;
    int c;
} Index;

void matrix_create(Matrix * m, int s, int c);
void matrix_add(Matrix * m, float value, Index ind);
float matrix_get_element(const Matrix * m, Index ind);
Matrix matrix_transform(Matrix m, float value);
int get_index(const Matrix * m, float value, Index * res);

void matrix_inner_print(const Matrix * m);
void matrix_print(const Matrix * m);



#endif