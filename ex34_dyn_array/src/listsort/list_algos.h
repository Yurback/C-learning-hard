#ifndef _list_algos_h
#define _list_algos_h

#include <lcthw/list.h>

int cmp(void*,void*);

int intcmp(void*, void*);

int intcmp_rev(void*, void*);

int strcmp_rev(void *, void *);

typedef int (*List_compare) (void*, void*);

int List_bubble_sort(List *list, List_compare);

List *List_merge_sort(List *list, List_compare);


#endif
