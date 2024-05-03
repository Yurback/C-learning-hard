#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <listsort/list_algos.h>

int intcmp(void *a, void *b)
{
	int aa = *(int *)a;
	int bb = *(int *)b;
	return aa - bb;
}

int intcmp_rev(void *a, void *b)
{
	int aa = *(int *)a;
	int bb = *(int *)b;
	return bb - aa;
}

int strcmp_rev(void *a, void *b)
{
	int res = -(strcmp((char *)a, (char *)b));
	return res;
}

int List_bubble_sort(List *list, int (*cmp)(void *, void *))
{

	if (list->first == NULL || (list->first == list->last))
		return 0;

	UPTO((list->count) - 1)
	{
		ListNode *cur = list->first;
		UPTO((list->count) - 1)
		{
			// Check cmpfunc
			if (cmp(cur->value, cur->next->value) > 0)
			{
				void *tmp = cur->value;
				cur->value = cur->next->value;
				cur->next->value = tmp;
			}
			cur = cur->next;
		}
	}

	return 0;
}

List *List_merge_sort(List *list, int (*cmp)(void *, void *))
{
	if (List_count(list) == 0)
		return NULL;
	if (List_count(list) == 1)
		return list;
	if (List_count(list) == 2)
	{
		ListNode *cur = list->first;
		if (cmp(cur->value, cur->next->value) > 0)
		{
			void *tmp = cur->value;
			cur->value = cur->next->value;
			cur->next->value = tmp;
		}
		return list;
	}
	int left = list->count / 2;
	int right = list->count - left;
	List *leftlist = List_create();
	List *rightlist = List_create();

	ListNode *cur = list->first;
	leftlist->first = cur;

	// Find last node from list for leftlist
	// Do rewind
	UPTO(left - 1)
	{
		cur = cur->next;
	}
	leftlist->last = cur;
	leftlist->count = left;

	// Work with rightlist
	cur = cur->next;
	rightlist->first = cur;
	UPTO(right - 1)
	{
		cur = cur->next;
	}
	rightlist->last = cur;
	rightlist->count = right;

	// recursion calling left list and right list and then merging
	leftlist = List_merge_sort(leftlist, cmp);
	rightlist = List_merge_sort(rightlist, cmp);

	ListNode *curleft = leftlist->first;
	ListNode *curright = rightlist->first;

	List *copylist = List_cpy(list);
	ListNode *copycur = copylist->first;

	while (leftlist->count > 0 || leftlist->count > 0)
	{
		if (leftlist->count <= 0)
		{
			copycur->value = curright->value;
			copycur = copycur->next;
			curright = curright->next;
			rightlist->count -= 1;
			continue;
		}
		if (rightlist->count <= 0)
		{
			copycur->value = curleft->value;
			copycur = copycur->next;
			curleft = curleft->next;
			leftlist->count -= 1;
			continue;
		}
		if (cmp(curleft->value, curright->value) > 0)
		{
			copycur->value = curright->value;
			copycur = copycur->next;
			curright = curright->next;
			rightlist->count -= 1;
		}
		else
		{
			copycur->value = curleft->value;
			copycur = copycur->next;
			curleft = curleft->next;
			leftlist->count -= 1;
		}
	}

	cur = list->first;
	copycur = copylist->first;
	UPTO(copylist->count)
	{
		cur->value = copycur->value;
		cur = cur->next;
		copycur = copycur->next;
	}
	free(leftlist);
	free(rightlist);
	List_destroy(copylist);
	return list;
}
