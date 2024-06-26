#include "minunit.h"
#include <tstree/tstree.h>
#include <assert.h>
#include <lcthw/bstrlib.h>

TSTree *node = NULL;
char *valueA = "VALUEA";
char *valueB = "VALUEB";
char *value2 = "VALUE2";
char *value4 = "VALUE4";
char *reverse = "VALUER";
int traverse_count = 0;

struct tagbstring test1 = bsStatic("TEST");
struct tagbstring test2 = bsStatic("TEST2");
struct tagbstring test3 = bsStatic("TSET");
struct tagbstring test4 = bsStatic("T");

char *test_insert()
{
    node = TSTree_insert(node, bdata(&test1), blength(&test1), valueA);
    mu_assert(node != NULL, "Failed to insert into tst");

    node = TSTree_insert(node, bdata(&test2), blength(&test2), value2);
    mu_assert(node != NULL, "Failed to insert into tst second name");

    node = TSTree_insert(node, bdata(&test3), blength(&test3), reverse);
    mu_assert(node != NULL, "Failed to insert into tst reverse name");

    node = TSTree_insert(node, bdata(&test4), blength(&test4), value4);
    mu_assert(node != NULL, "Failed to insert into tst with scond name");

    node = TSTree_insert(node, "AA", 2, "Apple");
    mu_assert(node != NULL, "Failed to insert into tst with scond name");
    return NULL;
}

char *test_search_exact()
{
    // tst returns the last one inserted
    void *res = TSTree_search(node, bdata(&test1), blength(&test1));
    mu_assert(res == valueA,
              "Got the wrong value back, should get A not B");

    // tst does not find if not exact
    res = TSTree_search(node, "TESTNO", strlen("TESTNO"));
    mu_assert(res == NULL, "Should not find anything.");

    // tst VALUEB what doesn't exist
    res = TSTree_search(node, valueB, strlen(valueB));
    mu_assert(res == NULL, "There is not node with value4");

    // tst AA
    res = TSTree_search(node, "AA", 2);
    mu_assert(strcmp(res, "Apple") == 0, "Apple not find");

    return NULL;
}

char *test_search_prefix()
{
    void *res = TSTree_search_prefix(
        node, bdata(&test1), blength(&test1));
    debug("result %p, expected: %p", res, valueA);
    mu_assert(res == valueA, "Got wrong valueA by prefix");
    res = TSTree_search_prefix(node, bdata(&test1), 1);
    mu_assert(res == value4, "Got wrong value4 for prefix of 1");

    res = TSTree_search_prefix(node, "TE", strlen("TE"));
    mu_assert(res != NULL, "Should find for short prefix");

    res = TSTree_search_prefix(node, "TE--", strlen("TE--"));
    mu_assert(res != NULL, "Should find for partial prefix");

    res = TSTree_search_prefix(node, "A", 1);
    mu_assert(strcmp(res, "Apple") == 0, "Got wrong apple for prefix of A");

    return NULL;
}

void TSTree_traverse_test_cb(void *value, void *data)
{
    assert(value != NULL && "Should not get NULL value");
    assert(data == valueA && "Expecting valueA as the data.");
    traverse_count++;
}

char *test_traverse()
{
    traverse_count = 0;
    TSTree_traverse(node, TSTree_traverse_test_cb, valueA);
    debug("traverse count is: %d", traverse_count);
    mu_assert(traverse_count == 5, "Didn't find 4 keys.");

    return NULL;
}

char *test_destroy()
{
    TSTree_destroy(node);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_insert);
    mu_run_test(test_search_exact);
    mu_run_test(test_search_prefix);
    mu_run_test(test_traverse);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);