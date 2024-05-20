#include <lcthw/list.h>
#include <lcthw/dbg.h>

#define Queue List
#define Queue_create List_create
#define Queue_destroy List_destroy
#define Queue_send List_push
#define Queue_peek List_first
#define Queue_count List_count
#define QUEUE_FOREACH(queue, cur) LIST_FOREACH(queue, first, next, cur)
#define Queue_recv List_shift