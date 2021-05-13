#include "vector.h"
#include "stack.h"
#include "merge_sort.h"
#include <stdio.h>

int main() {

    Stack s1;
    stack_create(&s1);
    int ch;
    char str[256];

    while(true) {
        printf("\nMenu: \n\t1) Add elements to stack.\n\t2) Print stack.\n\t3) Remove elements from stack.\n\t4) Sort stack.\n\t5) Exit.\n\nYour choice: ");
        
        do {
            fgets(str, sizeof(str), stdin);
        } while(sscanf(str, "%d", &ch) != 1);

        switch (ch)
        {
        case 1:
            printf("Enter key and value of element: ");
            SItem element;

            do {
                fgets(str, sizeof(str), stdin);
            } while (sscanf(str, "%d %s", &element.key, element.value) != 2);
            
            stack_push(&s1, element);
            
            break;
        
        case 2:
            printf("Stack:\n");
            stack_print(&s1);
            break;

        case 3:
            printf("Enter number of elemnts to delete: ");
            int dnum;
            do {
                fgets(str, sizeof(str), stdin);
            } while(sscanf(str, "%d", &dnum) != 1);

            if (dnum <= stack_size(&s1)) {
                for (int i = 0; i < dnum; ++i) {
                    stack_pop(&s1);
                }
            } else {
                printf("Incorrect value.");
            }

            break;

        case 4:
            printf("Sorted stack:\n");
            sort(&s1);
            stack_print(&s1);
            break;
            
        case 5:
            stack_destroy(&s1);
            return 0;

        default:
            continue;
        }
        

    }

}
