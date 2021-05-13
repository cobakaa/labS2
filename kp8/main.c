#include "list.h"
#include <string.h>

int main() {

    List list;
    list_create(&list);
    Item item;
    int ind;
    char str[256];
    int ch;
    int cnt = 0;

    while(true) {
        printf("\nMenu: \n\t1) Add element to list.\n\t2) Print list.\n\t3) Remove element from list.\n\t4) Print list size.\n\t5) Transform list.\n\t6) Exit.\n\nYour choice: ");
        
        do {
            fgets(str, sizeof(str), stdin);
        } while(sscanf(str, "%d", &ch) != 1);

        switch (ch)
        {
            case 1:
                
                do {
                    printf("Enter value of element: ");
                    scanf("%c", &item.value);
                    cnt = 0;
                    char c;
                    while ((c = getchar()) != EOF && c != '\n') cnt++;
                } while (cnt != 0);

                // do {
                //     printf("Enter value of element: ");
                //     fgets(str, sizeof(str), stdin);
                // } while (sscanf(str, "%s", &item.value) != 1 && strlen(item.value) == 1);

                do {
                    printf("Enter index: ");
                    fgets(str, sizeof(str), stdin);
                } while (sscanf(str, "%d", &ind) != 1);

                Iterator first = iterator_first(&list);
                Iterator insert = first;
                
                ind = (ind > list_size(&list)) ? list_size(&list) : ind;

                for (int i = 0; i < ind; ++i) {
                    insert = iterator_next(&first);
                }

                list_insert(&list, &insert, item);
                break;
                
            case 2:
                printf("List:\n");
                list_print(&list);
                break;

            case 3:
                printf("Enter element index to delete: ");
                int dnum;
                do {
                    fgets(str, sizeof(str), stdin);
                } while(sscanf(str, "%d", &dnum) != 1);

                if (dnum < list_size(&list)) {
                    Iterator first = iterator_first(&list);
                    Iterator delete = first;

                    for (int i = 0; i < dnum; ++i) {
                        delete = iterator_next(&first);
                    }

                    list_delete(&list, &delete);

                } else {
                    printf("Incorrect value.");
                }

                break;

            case 4:
                printf("List size: ");
                printf("%d\n", list_size(&list));

                break;

            case 5:
                printf("Enter k to swap (k-1) and (k+1) elements: ");
                int k;
                do {
                    fgets(str, sizeof(str), stdin);
                } while(sscanf(str, "%d", &k) != 1);
                if (list_swap_elements(&list, k)) {
                    printf("Elements were swapped.");
                }
                break;
                
            case 6:
                list_destroy(&list);
                return 0;

            default:
                continue;
        }
    }

}