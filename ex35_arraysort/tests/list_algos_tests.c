#include "minunit.h"
#include <listsort/list_algos.h>
#include <assert.h>
#include <string.h>

// char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
char *values[] = {"9", "5", "3", "88", "4"};

int integers[] = {150, 50, 10, 10, 75};

#define NUM_VALUES 5

List *create_int()
{
	int i = 0;
	List *ints = List_create();

	for (i = 0; i < NUM_VALUES; i++)
	{
		List_push(ints, &integers[i]);
	}

	return ints;
}

List *create_words()
{
	int i = 0;
	List *words = List_create();

	for (i = 0; i < NUM_VALUES; i++)
	{
		List_push(words, values[i]);
	}

	return words;
}

enum typevalue
{
	STR,
	INT
};

int is_sorted(List *list, enum typevalue type) //
{
	switch (type)
	{
	case STR:
	{
		LIST_FOREACH(list, first, next, cur)
		{
			if (cur->next && strcmp(cur->value, cur->next->value) > 0)
			{
				debug("%s %s", (char *)cur->value,
					  (char *)cur->next->value);
				return 0;
			}
		}
	}
	break;
	case INT:
	{
		LIST_FOREACH(list, first, next, cur)
		{
			if (cur->next && (*(int *)(cur->value) > *(int *)(cur->next->value)))
			{
				debug("%d %d", *(int *)(cur->value),
					  *(int *)(cur->next->value));
				return 0;
			}
		}
	}
	break;
	default:
		sentinel("We never should be here.");
	}

	return 1;

error:
	return 0;
}

int is_sorted_rev(List *list, enum typevalue type) //
{
	switch (type)
	{
	case STR:
	{
		LIST_FOREACH(list, first, next, cur)
		{
			if (cur->next && strcmp(cur->value, cur->next->value) < 0)
			{
				debug("%s %s", (char *)cur->value,
					  (char *)cur->next->value);
				return 0;
			}
		}
	}
	break;
	case INT:
	{
		LIST_FOREACH(list, first, next, cur)
		{
			if (cur->next && (*(int *)(cur->value) < *(int *)(cur->next->value)))
			{
				debug("%d %d", *(int *)(cur->value),
					  *(int *)(cur->next->value));
				return 0;
			}
		}
	}
	break;
	default:
		sentinel("We never should be here.");
	}

	return 1;

error:
	return 0;
}

char *test_bubble_sort()
{
	// _____________TEST STRING LIST VALUE ON ASCENDING ORDER_________________
	List *words = create_words();
	List_display(words, "str");
	// should work on a list that needs sorting

	int rc = List_bubble_sort(words, (List_compare)strcmp);
	mu_assert(rc == 0, "Bubble sort failed");
	mu_assert(is_sorted(words, STR), "Words are not sorted after bubble sort.");
	List_display(words, "str");
	// should work on an already sorted list
	rc = List_bubble_sort(words, (List_compare)strcmp);
	mu_assert(rc == 0, "Bubble sort of already sorted failed.");
	mu_assert(is_sorted(words, STR), "Words should be sort if already bubble sorted");
	List_display(words, "str");
	List_destroy(words);

	// should work on an empty list
	words = List_create();
	rc = List_bubble_sort(words, (List_compare)strcmp);
	mu_assert(rc == 0, "Bubble sort failed on empty list.");
	mu_assert(is_sorted(words, STR), "Words should be sorted if empty");
	List_display(words, "str");
	List_destroy(words);

	// _____________TEST STRING LIST VALUE ON DESCENDING OREDER_________________
	words = create_words();
	List_display(words, "str");
	// should work on a list that needs sorting

	rc = List_bubble_sort(words, (List_compare)strcmp_rev);
	mu_assert(rc == 0, "Bubble sort failed");
	mu_assert(is_sorted_rev(words, STR), "Words are not sorted after bubble sort.");
	List_display(words, "str");
	// should work on an already sorted list
	rc = List_bubble_sort(words, (List_compare)strcmp_rev);
	mu_assert(rc == 0, "Bubble sort of already sorted failed.");
	mu_assert(is_sorted_rev(words, STR), "Words should be sort if already bubble sorted");
	List_display(words, "str");
	List_destroy(words);

	// should work on an empty list
	words = List_create();
	rc = List_bubble_sort(words, (List_compare)strcmp_rev);
	mu_assert(rc == 0, "Bubble sort failed on empty list.");
	mu_assert(is_sorted_rev(words, STR), "Words should be sorted if empty");
	List_display(words, "str");
	List_destroy(words);

	// _____________TEST INTEGER LIST VALUE ON ASCENDING ORDER_________________
	List *ints = create_int();
	List_display(ints, "int");

	// should work on a list that needs sorting

	rc = List_bubble_sort(ints, (List_compare)intcmp);
	mu_assert(rc == 0, "Bubble sort failed");
	mu_assert(is_sorted(ints, INT), "Ints are not sorted after bubble sort.");
	List_display(ints, "int");
	// should work on an already sorted list
	rc = List_bubble_sort(ints, (List_compare)intcmp);
	mu_assert(rc == 0, "Bubble sort of already sorted failed.");
	mu_assert(is_sorted(ints, INT), "Ints should be sort if already bubble sorted");
	List_display(ints, "int");
	List_destroy(ints);

	// should work on an empty list
	ints = List_create();
	rc = List_bubble_sort(ints, (List_compare)intcmp);
	mu_assert(rc == 0, "Bubble sort failed on empty list.");
	mu_assert(is_sorted(ints, INT), "Ints should be sorted if empty");
	List_display(ints, "int");
	List_destroy(ints);

	// _____________TEST INTEGER LIST VALUE ON DESCENDING ORDER_________________
	ints = create_int();
	List_display(ints, "int");

	// should work on a list that needs sorting

	rc = List_bubble_sort(ints, (List_compare)intcmp_rev);
	mu_assert(rc == 0, "Bubble sort failed");
	mu_assert(is_sorted_rev(ints, INT), "Ints are not sorted after bubble sort.");
	List_display(ints, "int");
	// should work on an already sorted list
	rc = List_bubble_sort(ints, (List_compare)intcmp_rev);
	mu_assert(rc == 0, "Bubble sort of already sorted failed.");
	mu_assert(is_sorted_rev(ints, INT), "Ints should be sort if already bubble sorted");
	List_display(ints, "int");
	List_destroy(ints);

	// should work on an empty list
	ints = List_create();
	rc = List_bubble_sort(ints, (List_compare)intcmp_rev);
	mu_assert(rc == 0, "Bubble sort failed on empty list.");
	mu_assert(is_sorted_rev(ints, INT), "Ints should be sorted if empty");
	List_display(ints, "int");
	List_destroy(ints);
	return NULL;
}

char *test_merge_sort()
{
	// _____________TEST STRING LIST VALUE ON ASCENDING ORDER_________________
	List *words = create_words();

	// should work on a list that needs sorting
	List *res = List_merge_sort(words, (List_compare)strcmp);
	mu_assert(is_sorted(res, STR), "Word are not sorted after merge sort");

	List *res2 = List_merge_sort(res, (List_compare)strcmp);
	mu_assert(is_sorted(res2, STR), "should still be sorted after merge sort");
	List_display(words, "str");
	List_destroy(words);

	// _____________TEST STRING LIST VALUE ON DESCENDING ORDER_________________
	words = create_words();

	// should work on a list that needs sorting
	res = List_merge_sort(words, (List_compare)strcmp_rev);
	mu_assert(is_sorted_rev(res, STR), "Word are not sorted after merge sort");

	res2 = List_merge_sort(res, (List_compare)strcmp_rev);
	mu_assert(is_sorted_rev(res2, STR), "should still be sorted after merge sort");
	List_display(words, "str");
	List_destroy(words);

	// _____________TEST INTEGER LIST VALUE ON ASCENDING ORDER_________________
	List *ints = create_int();

	// should work on a list that needs sorting
	res = List_merge_sort(ints, (List_compare)intcmp);
	mu_assert(is_sorted(res, INT), "Integers are not sorted after merge sort");

	res2 = List_merge_sort(res, (List_compare)intcmp);
	mu_assert(is_sorted(res2, INT), "Integers still be sorted after merge sort");
	List_display(ints, "int");
	List_destroy(ints);

	// _____________TEST INTEGER LIST VALUE ON DESCENDING ORDER_________________
	ints = create_int();

	// should work on a list that needs sorting
	res = List_merge_sort(ints, (List_compare)intcmp_rev);
	mu_assert(is_sorted_rev(res, INT), "Integers are not sorted after merge sort");

	res2 = List_merge_sort(res, (List_compare)intcmp_rev);
	mu_assert(is_sorted_rev(res2, INT), "Integers still be sorted after merge sort");
	List_display(ints, "int");
	List_destroy(ints);
	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_bubble_sort);
	mu_run_test(test_merge_sort);

	return NULL;
}

RUN_TESTS(all_tests);
