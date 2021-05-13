#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void matrix_create(Matrix * m, int s, int c) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        m->CIP[i] = 0;
        m->PI[i] = 0;
        m->YE[i] = 0.0;
    }

    m->CIP[MAX_SIZE + 1] = 0;
    m->K = 0;
    m->N = c;
    m->M = s;
}

void matrix_add(Matrix * m, float value, Index ind) {
    if (value == 0.0) {
        return;
    }

    m->YE[m->K] = value;
    m->PI[m->K] = ind.c;
    m->K++;
    if (m->CIP[ind.s - 1] == 0) {
        m->CIP[ind.s - 1] = m->K;
    }
}

// float abs(float x) {
//     return (x > 0) ? x : -x;
// }

float matrix_get_element(const Matrix * m, Index ind) {

    if (m->CIP[ind.s - 1] == 0) {
        return 0.0;
    }

    int s1 = (ind.s == m->M) ? abs(m->K - m->CIP[ind.s - 1] + 1) : abs(m->CIP[ind.s] - m->CIP[ind.s - 1]);
    for (int i = m->CIP[ind.s - 1] - 1; i < m->CIP[ind.s - 1] - 1 + s1; ++i) {
        if (m->PI[i] == ind.c) {
            return m->YE[i];
        }
    }

    return 0.0;
}

void divide_element(Matrix * m, Index ind, float value) {
    if (m->CIP[ind.s - 1] == 0) {
        return;
    }

    int s1 = (ind.s == m->M) ? abs(m->K - m->CIP[ind.s - 1] + 1) : abs(m->CIP[ind.s] - m->CIP[ind.s - 1]);
    for (int i = m->CIP[ind.s - 1] - 1; i < m->CIP[ind.s - 1] - 1 + s1; ++i) {
        if (m->PI[i] == ind.c) {
            m->YE[i] /= value;
            break;
        }
    }
}

void matrix_inner_print(const Matrix * m) {
    printf("CIP = ");
    printf("(");
    for (int i = 0; i < m->M; ++i) {
        printf("%d", m->CIP[i]);
        if (i != m->M - 1) {
            printf(",");
        }
    }
    printf(")\n");    
    printf("PI = ");
    printf("(");
    for (int i = 0; i < m->K; ++i) {
        printf("%d", m->PI[i]);
        if (i != m->K - 1) {
            printf(",");
        }
    }
    printf(")\n");  
    printf("YE = ");
    printf("(");
    for (int i = 0; i < m->K; ++i) {
        printf("%g", m->YE[i]);
        if (i != m->K - 1) {
            printf(",");
        }
    }
    printf(")\n");
}

int get_index(const Matrix * m, float value, Index * res) {
    Index tmp;
    tmp.s = 0;
    tmp.c = 0;
    if (m->K < 1) {
        return 0;
    }

    // Index inds[MAX_SIZE];
    int inds_count = 0;

    for (int i = 0; i < m->K; ++i) {
        if (m->YE[i] == value) {
            tmp.c = m->PI[i];

            for (int i = 1; i <= m->M; ++i) {
                int s1 = (i == m->M) ? abs(m->K - m->CIP[i - 1] + 1) : abs(m->CIP[i] - m->CIP[i - 1]);
                for (int j = m->CIP[i - 1] - 1; j < m->CIP[i - 1] - 1 + s1; ++j) {
                    if (m->PI[j] == tmp.c && m->YE[j] == value) {
                        tmp.s = i;
                        res[inds_count++] = tmp;
                        break;
                    }
                }
            }

        }
    }
    return inds_count;
}

Matrix matrix_transform(Matrix m, float value) {
    float diffs[2];
    int min_count = 1;
    if (m.K < 1) {
        return m;
    }
    float min_diff = fabs(m.YE[0] - value);
    diffs[0] = m.YE[0];
    
    for (int i = 1; i < m.K; ++i) {
        if (fabs(m.YE[i] - value) < min_diff) {
            min_count = 1;
            diffs[0] = m.YE[i];
            min_diff = fabs(m.YE[i] - value);
        } else if (fabs(m.YE[i] - value) == min_diff && diffs[0] != min_diff && diffs[1] != min_diff) {
            diffs[min_count++] = m.YE[i];
        }
    }

    Matrix res;
    matrix_create(&res, m.M, m.N);
    res = m;
    Index * inds = (Index*)malloc(sizeof(Index) * MAX_SIZE);
    for (int i = 0; i < min_count; ++i) {
        int inds_count = get_index(&m, diffs[i], inds);

        for (int j = 0; j < inds_count; ++j) {
            Index t;
            t.s = inds[j].s;
            t.c = inds[j].c;
            divide_element(&res, t, value);
            for (int k = 1; k <= res.M; ++k) {
                if (k != t.s) {
                    Index tt;
                    tt.c = t.c;
                    tt.s = k;
                    divide_element(&res, tt, value);
                }
            }

            for (int k = 1; k <= res.N; ++k) {
                if (k != t.c) {
                    Index tt;
                    tt.s = t.s;
                    tt.c = k;
                    divide_element(&res, tt, value);
                }
            }
        }
    }

    free(inds);
    
    return res;
}

void matrix_print(const Matrix * m) {
    for (int i = 0; i < m->M; ++i) {
        for (int j = 0; j < m->N; ++j) {
            Index ind;
            ind.s = i + 1;
            ind.c = j + 1;
            printf("%8g ", matrix_get_element(m, ind));
            // matrix_add(&m, elem, i + 1, j + 1);
        }
        printf("\n");
    }
}

void matrix_clear(Matrix * m) {
    matrix_create(m, 0, 0);
}

bool matrix_empty(const Matrix * m) {
    return m->M == 0 || m->N == 0;
}