#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    Matrix m;

    int ch;
    char str[256];

    while(true) {
        printf("\nMenu: \n\t1) Enter matrix.\n\t2) Print matrix.\n\t3) Transform matrix.\n\t4) Exit.\n\nYour choice: ");
        
        do {
            fgets(str, sizeof(str), stdin);
        } while(sscanf(str, "%d", &ch) != 1);

        switch (ch)
        {
        case 1:
            printf("Enter matrix size: ");
            int s, c;

            do {
                fgets(str, sizeof(str), stdin);
            } while (sscanf(str, "%d %d", &s, &c) != 2);
            
            matrix_create(&m, s, c); 

            printf("Enter matrix elements:\n");

            float element;
            Index ind;
            for (int i = 0; i < s; ++i) {
                for (int j = 0; j < c; ++j) {
                    scanf("%f", &element);
                    ind.s = i + 1;
                    ind.c = j + 1;
                    matrix_add(&m, element, ind);
                }
            }
            
            break;
        
        case 2:
            printf("Matrix:\n");
            matrix_print(&m);
            printf("---------\n");

            matrix_inner_print(&m);
            break;

        case 3:
            printf("Enter value to matrix trnsfom: ");
            float value;
            scanf("%f", &value);
            m = matrix_transform(m, value);
            // matrix_print(&m);
            printf("Matrix transformed.\n");
            break;
            
        case 4:
            return 0;

        default:
            continue;
        }
        

    }


    return 0;
}