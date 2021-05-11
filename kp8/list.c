#include "list.h"

bool iterator_equal(const Iterator* lhs, const Iterator* rhs) {
    return (lhs->node == rhs->node) && (lhs->begin == rhs->begin);
}

Iterator iterator_next(Iterator* i) {
    i->node = i->begin[i->node].next;
    return *i;
}

Iterator iterator_first(const List* l) {
    Iterator res = {l->data, l->data[l->head].next};
    return res;
}

Iterator iterator_last(const List* l) {
    Iterator res = {l->data, l->head};
    return res;
}

Item iterator_fetch(const Iterator* i) {
    return i->begin[i->node].data;
}

void iterator_store(const Iterator* i, const Item t) {
    i->begin[i->node].data = t;
}

Iterator iterator_prev(List *list, Iterator * it) {
    Iterator first = iterator_first(list);
	Iterator res = first;

	if (it->node == -1)
		return iterator_last(list);

	while (res.begin[res.node].next != it->node)
		res = iterator_next(&first);

	return res;
}

void list_create(List* l, int list_size) {

    if (list_size < 1)
		return;

	l->data = (LItem *)malloc(sizeof(LItem) * (list_size + 1));

    for (int i = 0; i < list_size; ++i) {
        l->data[i].next = i + 1;
    }

    l->data[list_size - 1].next = -1;
    l->head = list_size;
    l->data[l->head].next = l->head;
    l->top = 0;
    l->capacity = list_size;
    l->size = 0;
}

Iterator list_insert(List* l, Iterator* i, const Item t) {
    // if (l->size == l->capacity)
	// {
	// 	printf("List is full\n");

	// 	return *i;
	// }
    Iterator res;
    res.begin = l->data;
    res.node = l->top;
    if (res.node == -1) {
        return iterator_last(l);
    }

    l->top = l->data[l->top].next;

    
    res.begin[res.node].data = t;
    res.begin[res.node].next = i->node;
    Iterator prev = iterator_prev(l, i);
    res.begin[prev.node].next = res.node;

    l->size++;

    return res;
}

Iterator list_delete(List* l, Iterator* i) {
    Iterator res = iterator_last(l);
    if (iterator_equal(i, &res)) {
        return res;
    }

    Iterator i_prev = iterator_prev(l, i);
    res.node = i->begin[i->node].next;
    i->begin[i_prev.node].next = res.node;
    l->size--;

    i->begin[i->node].next = l->top;

    l->top = i->node;
    i->node = -1;
    return res;
}

void list_destroy(List * l) {
    l->head = 0;
    l->size = 0;
    l->top = 0;
    free(l->data);
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

void list_change_elements(List * l, int k) {
    if (k <= 0 || k >= list_size(l) - 1 || list_size(l) < 3) {
        printf("Incorrect value.\n");
        return;
    }

    Iterator first = iterator_first(l);
    Iterator cur = first;

    for (int i = 0; i < k; ++i) {
        cur = iterator_next(&first);
    }

    Iterator prev = iterator_prev(l, &cur);
    Iterator next = iterator_next(&cur);
    // next = iterator_next(&cur);
    LItem tmp_next = next.begin[next.node];
    LItem tmp_prev = prev.begin[prev.node];
    
    list_delete(l, &next);
    list_delete(l, &prev);

    first = iterator_first(l);
    cur = first;
    
    for (int i = 0; i < k - 1; ++i) {
        cur = iterator_next(&first);
    }

    list_insert(l, &cur, tmp_next.data);
    cur = iterator_next(&cur);
    // cur = iterator_next(&cur);
    list_insert(l, &cur, tmp_prev.data);
}