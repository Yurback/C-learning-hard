#include <libarray/darray.h>
#include <assert.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
	DArray *array = calloc(1, sizeof(DArray));
	check_mem(array);
	array->max = initial_max;
	check(array->max > 0, "You must set an initial_max > 0.");
	array->contents = calloc(initial_max, sizeof(void *));
	check_mem(array->contents);

	array->size = 0; // 0 means empty
	array->element_size = element_size;
	array->expand_rate = DEFAULT_EXPAND_RATE;

	return array;

error:
	if (array)
	{
		if (array->contents)
			free(array->contents);
		free(array);
	}
	return NULL;
}

void DArray_clear(DArray *array)
{
	int i = 0;
	if (array->element_size > 0)
	{
		for (i = 0; i < array->max; i++)
		{
			if (array->contents[i] != NULL)
			{
				free(array->contents[i]);
			}
		}
	}
}

static inline int DArray_resize(DArray *array, size_t newsize)
{
	array->max = newsize;
	check(array->max > 0, "The newsize must be > 0");

	void *contents = realloc(
		array->contents, array->max * sizeof(void *));
	// check contents and assume realloc doesn't harm the original on error

	check_mem(contents);
	array->contents = contents;

	return 0;
error:
	return -1;
}

int DArray_expand(DArray *array)
{
	size_t old_max = array->max;
	check(DArray_resize(array, array->max + array->expand_rate) == 0,
		  "Failed to expand array to new size: %d", array->max + (int)array->expand_rate);
	memset(array->contents + old_max, 0, (array->expand_rate) * sizeof(void *)); // FIX flow in Zed code
	return 0;

error:
	return -1;
}

int DArray_contract(DArray *array)
{
	int new_size = array->size < (int)array->expand_rate ? (int)array->expand_rate : array->size;
	return DArray_resize(array, new_size);
}

int DArray_contract_min(DArray *array)
{
	int new_size = array->size;
	return DArray_resize(array, new_size);
}

void DArray_destroy(DArray *array)
{
	if (array)
	{
		if (array->contents)
			free(array->contents);
		free(array);
	}
}

void DArray_clear_destroy(DArray *array)
{
	DArray_clear(array);
	DArray_destroy(array);
}

int DArray_push(DArray *array, void *el)
{
	if (DArray_size(array) + 1 > DArray_max(array))
	{
		int rc = DArray_expand(array);
		check(rc == 0, "Fail in expand array");
	}
	array->size++;

	array->contents[array->size - 1] = el;

	return 0;

error: // fallthrough
	return -1;
}

void *DArray_pop(DArray *array)
{

	if (array->size == 0)
		return NULL;
	void *el = DArray_remove(array, array->size - 1);
	array->size--;

	if (DArray_max(array) - DArray_size(array) >= (int)array->expand_rate)
	{
		DArray_contract(array);
	}

	return el;
}

int DArray_display(DArray *array, char mode)
{
	if (mode == 'a')
	{
		printf("=============DArray_info==============\n");
		UPTO(array->max)
		{
			printf("Element: %d ; Value : %s \n", i, (char *)array->contents[i]);
		}
		printf("=======================================\n");
	}
	else
	{
		printf("=============DArray_info==============\n");
		UPTO(array->size)
		{
			printf("Element: %d ; Value : %s \n", i, (char *)array->contents[i]);
		}
		printf("=======================================\n");
	}
	return 0;
}