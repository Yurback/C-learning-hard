#include "lcthw/list.h"
#include "lcthw/dbg.h"

List *List_create()
{
	return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
	LIST_FOREACH(list, first, next, cur)
	{
		if (cur->prev)
		{
			free(cur->prev);
		}
	}

	free(list->last);
	free(list);
}

void List_clear(List *list)
{
	LIST_FOREACH(list, first, next, cur)
	{
		free(cur->value);
	}
}

void List_clear_destroy(List *list)
{
	List_clear(list);
	List_destroy(list);
}

void List_push(List *list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if (list->last == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}

	list->count++;
error:
	return;
}

void *List_pop(List *list)
{
	ListNode *node = list->last;
	return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if (list->first == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}

	list->count++;

error:
	return;
}

void *List_shift(List *list)
{
	ListNode *node = list->first;
	return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
	void *result = NULL;

	check(list->first && list->last, "List is empty.");
	check(node, "node can't be NULL");

	if (node == list->first && node == list->last)
	{
		list->first = NULL;
		list->last = NULL;
	}
	else if (node == list->first)
	{
		list->first = node->next;
		check(list->first != NULL,
			  "Invalid list, somehow got a first that is NULL.");
		list->first->prev = NULL;
	}
	else if (node == list->last)
	{
		list->last = node->prev;
		check(list->last != NULL,
			  "Invalid list, somehow got a next that is NULL.");
		list->last->next = NULL;
	}
	else
	{
		ListNode *after = node->next;
		ListNode *before = node->prev;
		after->prev = before;
		before->next = after;
	}

	list->count--;
	result = node->value;
	free(node);
error:
	return result;
}

void List_display(List *list, char *type)
{
	check(list->first && list->last, "List is empty.");
	int number = 1;
	if (strcmp(type, "str") == 0)
	{
		LIST_FOREACH(list, first, next, cur)
		{
			if (cur->value)
			{
				printf("Node %d : Value %s\n", number, (char *)cur->value);
				debug("Node %d : Value %s\n", number, (char *)cur->value);
				number++;
			}
		}
		printf("===================================\n");
	}
	else if (strcmp(type, "int") == 0)
	{
		LIST_FOREACH(list, first, next, cur)
		{
			if (cur->value)
			{
				printf("Node %d : Value %d\n", number, *(int *)cur->value);
				debug("Node %d : Value %d\n", number, *(int *)cur->value);
				number++;
			}
		}
		printf("===================================\n");
	}
error:
	return;
}

List *List_cpy(List *oldlist)
{
	check(oldlist->first && oldlist->last, "List is empty.");
	List *newlist = List_create();
	LIST_FOREACH(oldlist, first, next, cur)
	{
		List_push(newlist, cur->value);
	}

	return newlist;
error:
	return NULL;
}
