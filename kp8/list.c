#include "list.h"

bool iterator_equal(const Iterator* lhs, const Iterator* rhs) {
    return (lhs->node == rhs->node);
}

Iterator iterator_next(Iterator* i) {
    i->node = i->node->next;
    return *i;
}

Iterator iterator_first(const List* l) {
    Iterator res = {l->head->next};
    return res;
}

Iterator iterator_last(const List* l) {
    Iterator res = {l->head};
    return res;
}

Item iterator_fetch(const Iterator* i) {
    return i->node->data;
}

void iterator_store(const Iterator* i, const Item t) {
    i->node->data = t;
}

Iterator iterator_prev(List * l, Iterator * it) {
    Iterator first = iterator_first(l);
	Iterator res = first;

	while (res.node->next != it->node)
		res = iterator_next(&first);

	return res;
}

void list_create(List* l) {

    l->head = (struct LItem *)malloc(sizeof(struct LItem));
    l->head->next = l->head;
    l->size = 0;
}

Iterator list_insert(List* l, Iterator* i, const Item t) {
    // Iterator prev = iterator_prev(l, i);
    Iterator res = { (struct LItem *)malloc(sizeof(struct LItem)) };
    if (!res.node) {
        return iterator_last(l);
    }

    res.node->data = t;
    res.node->next = i->node;
    Iterator prev = iterator_prev(l, i);
    prev.node->next = res.node;
    l->size++;
    return res;

}

Iterator list_delete(List* l, Iterator* i) {
    Iterator res = iterator_last(l);
    if (iterator_equal(i, &res)) {
        return res;
    }

    Iterator i_prev = iterator_prev(l, i);
    res.node = i->node->next;
    i_prev.node->next = res.node;
    l->size--;

    free(i->node);
    i->node = NULL;
    return res;
}

void list_destroy(List * l) {
    struct LItem * i = l->head->next;
    while (i != l->head)
    {
        struct LItem * tmp = l->head->next;
        i = i->next;
        l->head->next = i;
        free(tmp);

    }
    free(l->head);
    l->head = NULL;
    l->size = 0;
    
}

int list_size(const List* l) {
    return l->size;
}

bool list_empty(const List* l) {
    Iterator first = iterator_first(l);
    Iterator last = iterator_last(l);

    return iterator_equal(&first, &last);
}


void list_print(const List* l) {
    Iterator cur = iterator_first(l);
    Iterator last = iterator_last(l);
    while (!iterator_equal(&cur, &last)) {
        printf(" %c\n", iterator_fetch(&cur).value);
        cur = iterator_next(&cur);
    }
}

bool list_swap_elements(List * l, int k) {
    if (k <= 0 || k >= list_size(l) - 1 || list_size(l) < 3) {
        printf("Incorrect value.\n");
        return false;
    }

    Iterator first = iterator_first(l);
    Iterator cur = first;

    for (int i = 0; i < k - 1; ++i) {
        cur = iterator_next(&first);
    }

    // cur.node->next = cur.node->next->next;
    LItem * prev_prev = iterator_prev(l, &cur).node;
    LItem * prev = cur.node;
    LItem * it_k = iterator_next(&cur).node;
    LItem * next = iterator_next(&cur).node;
    

    it_k->next = prev;
    prev->next = next->next;
    next->next = it_k;
    prev_prev->next = next;
    

    return true;
}