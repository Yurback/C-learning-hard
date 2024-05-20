#include <lcthw/list.h>
#include <lcthw/dbg.h>

#define Queue List
#define Queue_create() List_create()
#define Queue_destroy(queue) List_destroy(queue)
#define Queue_send(queue, value) List_push(queue, value)
#define Queue_peek(queue) List_first(queue)
#define Queue_count(queue) List_count(queue)
#define QUEUE_FOREACH(queue, cur) LIST_FOREACH(queue, first, next, cur)
#define Queue_recv(queue) List_shift(queue)