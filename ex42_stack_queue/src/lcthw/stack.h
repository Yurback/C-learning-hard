#include <lcthw/list.h>
#include <lcthw/dbg.h>

#define Stack List
#define Stack_create List_create
#define Stack_destroy List_destroy
#define Stack_push List_push
#define Stack_peek List_last
#define Stack_count List_count
#define STACK_FOREACH(stack, cur) LIST_FOREACH(stack, last, prev, cur)
#define Stack_pop List_pop
