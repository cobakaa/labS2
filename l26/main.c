#include "vector.h"
#include "stack.h"
#include "merge_sort.h"
#include <stdio.h>

int main() {

    Stack s1;
    stack_create(&s1);

    int num;

    while (scanf("%d", &num) == 1)
    {
        stack_push(&s1, num);
    }
    
    stack_print(&s1);
    
    sort(&s1);
    stack_print(&s1);
    stack_destroy(&s1);


    return 0;
}