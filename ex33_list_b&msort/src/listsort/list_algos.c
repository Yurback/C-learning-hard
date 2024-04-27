#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <listsort/list_algos.h>


int intcmp(void*a, void*b) {
	int aa = *(int*)a;
	int bb = *(int*)b;
	return aa-bb;
}

int List_bubble_sort(List *list, int (*cmp)(void*,void*)) {
	
	if(list->first == NULL || (list->first == list->last))
		return 0;
	
	UPTO((list->count)-1)
	{
		ListNode *cur = list->first;
		UPTO((list->count)-1)
		{
			// Check cmpfunc
			if(cmp(cur->value, cur->next->value) > 0) {
				void *tmp = cur->value;
				cur->value = cur->next->value;
				cur->next->value = tmp;
			}
			cur = cur->next;	
		}	
	}
	
	return 0;

}
