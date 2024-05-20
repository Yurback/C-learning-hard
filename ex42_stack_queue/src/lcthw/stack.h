#include <lcthw/list.h>
#include <lcthw/dbg.h>

#define Stack List
#define Stack_create() List_create()
#define Stack_destroy(stack) List_destroy(stack)
#define Stack_push(stack, value) List_push(stack, value)
#define Stack_peek(stack) List_last(stack)
#define Stack_count(stack) List_count(stack)
#define STACK_FOREACH(stack, cur) LIST_FOREACH(stack, first, next, cur)
#define Stack_pop(stack) List_pop(stack)
