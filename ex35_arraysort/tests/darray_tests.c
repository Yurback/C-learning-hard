#include "minunit.h"
#include <libarray/darray.h>
#include <lcthw/dbg.h>

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
	array = DArray_create(sizeof(int), 100);
	mu_assert(array != NULL, "DArray_create failed.");
	mu_assert(array->contents != NULL, "contents are wrong in darray");
	mu_assert(array->size == 0, "end isn't at the right spot");
	mu_assert(array->element_size == sizeof(int), "element size is wrong.");
	mu_assert(array->max == 100, "wrong max length on initial size");

	return NULL;
}

char *test_destroy()
{
	DArray_destroy(array);

	return NULL;
}

char *test_new()
{
	val1 = DArray_new(array);
	mu_assert(val1 != NULL, "failed to make a new element");
	*val1 = 1500;
	val2 = DArray_new(array);
	mu_assert(val2 != NULL, "failed to make a new element");
	*val2 = 2000;
	return NULL;
}

char *test_set()
{
	DArray_set(array, 0, val1);
	DArray_set(array, 1, val2);

	return NULL;
}

char *test_get()
{
	mu_assert(DArray_get(array, 0) == val1, "Wrong first value.");
	mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");
	return NULL;
}

char *test_remove()
{
	int *val_check = DArray_remove(array, 0);
	mu_assert(val_check != NULL, "Should not get NULL.");
	mu_assert(*val_check == *val1, "Should get the first value.");
	mu_assert(DArray_get(array, 0) == NULL, "Should be gone.");
	DArray_free(val_check);

	val_check = DArray_remove(array, 1);
	mu_assert(val_check != NULL, "Should not get NULL.");
	mu_assert(*val_check == *val2, "Should get the value");
	mu_assert(DArray_get(array, 1) == NULL, "Should be gone");
	DArray_free(val_check);

	return NULL;
}

char *test_expand_contract()
{
	int old_max = array->max;
	DArray_expand(array);
	mu_assert((unsigned int)array->max == old_max + array->expand_rate,
			  "Wrong size after expand.");
	DArray_contract(array);
	mu_assert((unsigned int)array->max == array->expand_rate,
			  "Should stay at the expand_rate at least.");
	DArray_contract_min(array);
	mu_assert(array->max == array->size,
			  "Should stay at the expand_rate at least.");
	return NULL;
}

char *test_push_pop()
{
	int i = 0;
	for (i = 0; i < 1000; i++)
	{
		int *val = DArray_new(array);
		*val = i * 333;
		DArray_push(array, val);
	}
	mu_assert(array->max == 1202, "Wrong max size");

	for (i = 999; i >= 0; i--)
	{
		int *val = DArray_pop(array);
		mu_assert(val != NULL, "Shouldn't get a NULL");
		mu_assert(*val == i * 333, "Wrong value");
		DArray_free(val);
	}

	return NULL;
}

char *test_display()
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		int *val = DArray_new(array);
		*val = rand() % 350;
		DArray_push(array, val);
	}
	mu_assert(array->max = 300, "Wrong max size");

	DArray_display(array, 'e', 'i');

	DArray_clear(array);
	mu_assert(!array->contents[array->size - 1], "Darray after clear_destroy must be NULL");

	char *val = calloc(1, 1);
	*val = 'a';
	DArray_set(array, 0, val);
	mu_assert(*(char *)(array->contents[0]) == 'a', "First element must be NULL");

	DArray_remove_free(array, 0);
	mu_assert(!array->contents[0], "First element must be NULL");

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_new);
	mu_run_test(test_set);
	mu_run_test(test_get);
	mu_run_test(test_remove);
	mu_run_test(test_expand_contract);
	mu_run_test(test_push_pop);
	mu_run_test(test_display);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TESTS(all_tests);
