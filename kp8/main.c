#include "list.h"

int main() {

    List l;
    list_create(&l, 100);
    Item item;
    int ind;

    for (int i = 0; i < 5; ++i) {
        scanf("%s %d", &item.value, &ind);
        
        Iterator first = iterator_first(&l);
        Iterator insert = first;

        
        // scanf("%d", &ind);
        ind = (ind > list_size(&l)) ? list_size(&l) : ind;
        

        for (int i = 0; i < ind; ++i) {
            insert = iterator_next(&first);
        }

        list_insert(&l, &insert, item);
    }

    list_print(&l);


    printf("--------\n");

    scanf("%d", &ind);
    
    // scanf("%d", &ind);
    // ind = (ind > list_size(&l)) ? list_size(&l) : ind;

    list_change_elements(&l, ind);

    list_print(&l);


    return 0;
}