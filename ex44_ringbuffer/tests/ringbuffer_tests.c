#include "minunit.h"
#include <ringbuf/ringbuffer.h>

static RingBuffer *buffer = NULL;
char data[12] = {'\0'};

char *test_create()
{
    buffer = RingBuffer_create(12);
    mu_assert(buffer != NULL, "Faild to make ringbuffer.");

    return NULL;
}

char *test_destroy()
{
    RingBuffer_destroy(buffer);

    return NULL;
}

char *test_read_write()
{
    mu_assert(RingBuffer_empty(buffer), "Should be empty");
    mu_assert(!RingBuffer_full(buffer), "Should NOT be full.");
    debug("data is: %d, spase is: %d",
          RingBuffer_available_data(buffer),
          RingBuffer_available_space(buffer));
    mu_assert(RingBuffer_available_data(buffer) == 0,
              "Should have 0 data");
    mu_assert(RingBuffer_available_space(buffer) == 12,
              "Should have 12 space.");

    int rc = RingBuffer_write(buffer, "hello", sizeof("hello"));
    mu_assert(rc == sizeof("hello"), "Failed to write hello.");
    mu_assert(RingBuffer_available_data(buffer) == 6,
              "Should have 6 data");
    mu_assert(RingBuffer_available_space(buffer) == 12 - 6,
              "Should have 6 space.");

    rc = RingBuffer_write(buffer, "Zed", sizeof("Zed"));
    mu_assert(rc == sizeof("Zed"), "Failed to write Zed");
    debug("buffer %s size %ld", buffer->buffer + 6, sizeof("zed"));

    mu_assert(!RingBuffer_empty(buffer), "Should Not be empty");
    mu_assert(!RingBuffer_full(buffer), "Should Not be full");

    rc = RingBuffer_write(buffer, "Yurback", sizeof("Zed"));
    mu_assert(rc == -1, "Must Failed to write Yurback");

    rc = RingBuffer_read(buffer, data, sizeof("hello"));
    mu_assert(rc == sizeof("hello"), "Failed to read the hello out");

    mu_assert(!RingBuffer_empty(buffer), "Should be empty");
    mu_assert(!RingBuffer_full(buffer), "Should Not be full");

    rc = RingBuffer_read(buffer, data, sizeof("Zed"));
    mu_assert(rc == sizeof("Zed"), "Failed to read the Zed out");
    mu_assert(RingBuffer_empty(buffer), "Should be empty");

    bstring data = bfromcstr("Hello Again");
    rc = RingBuffer_puts(buffer, data);
    bdestroy(data);
    mu_assert(rc != -1, "Failed to write a bstring");
    mu_assert(!RingBuffer_empty(buffer), "Should NOT be empty");

    data = RingBuffer_gets(buffer, 2);
    mu_assert(data, "Didn't get any bstring from gets");
    mu_assert(bisstemeqblk(data, "He", 2), "Wrong gets result");
    bdestroy(data);

    data = RingBuffer_get_all(buffer);
    mu_assert(data, "Didn't get any bstring from gets");
    mu_assert(bisstemeqblk(data, "llo Again", 9),
              "Wrong get_all result.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);