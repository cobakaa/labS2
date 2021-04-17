#include "merge_sort.h"


Stack merge(Stack * s1, Stack * s2) {
    Stack res;
    stack_create(&res);

    SItem s1_item, s2_item;
    while (!stack_is_empty(s1) && !stack_is_empty(s2))
    {
        s1_item = stack_pop(s1);
        s2_item = stack_pop(s2);

        if (s1_item > s2_item) {
            stack_push(&res, s2_item);
            stack_push(s1, s1_item);
        } else {
            stack_push(&res, s1_item);
            stack_push(s2, s2_item);
        }
    }

    while (!stack_is_empty(s1))
    {
        s1_item = stack_pop(s1);
        stack_push(&res, s1_item);
    }

    while (!stack_is_empty(s2)) {
        s2_item = stack_pop(s2);
        stack_push(&res, s2_item);
    }

    reverse(&res);

    return res;
    
}



void sort(Stack * s) {

    if (stack_size(s) <= 1) {
        return;
    }

    Stack res, tmp1, tmp2;
    stack_create(&res);
    stack_create(&tmp1);
    stack_create(&tmp2);

    size_t ssize = stack_size(s);

    for (int i = 0; i < ssize / 2; ++i) {
        SItem item = stack_pop(s);
        stack_push(&tmp1, item);
    }
    reverse(&tmp1);

    while (!stack_is_empty(s)) {
        SItem item = stack_pop(s);
        stack_push(&tmp2, item);
    }
    reverse(&tmp2);

    sort(&tmp1);
    sort(&tmp2);

    res = merge(&tmp1, &tmp2);

    stack_destroy(&tmp1);
    stack_destroy(&tmp2);

    stack_copy(s, &res);
}

void reverse(Stack * s) {

    Stack reversed;
    stack_create(&reversed);

    while (!stack_is_empty(s))
    {
        SItem item = stack_pop(s);
        stack_push(&reversed, item);
    }
    
    stack_copy(s, &reversed);

}