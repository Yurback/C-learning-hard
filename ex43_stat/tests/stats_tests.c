#include "minunit.h"
#include <stats/stats.h>
#include <math.h>

const int NUM_SAMPLES = 10;
double samples[] = {
    1.195402, 6.000738, 5.424882, 2.813227, 5.102216, 1.037505, 5.195159, 9.094582,
    2.369712, 3.834692};
Stats expect = {
    .sumsq = 231.912,
    .sum = 42.06811,
    .min = 1.038,
    .max = 9.095,
    .n = 10,
};

double expect_mean = 4.207;
double expect_stddev = 2.470702;

#define EQ(X, Y, N) (round((X) * pow(10, N)) == round((Y) * pow(10, N)))

char *test_operations()
{
    int i = 0;
    Stats *st = Stats_create();
    mu_assert(st != NULL, "Failed to create stats");

    for (i = 0; i < NUM_SAMPLES; i++)
    {
        Stats_sample(st, samples[i]);
    }

    Stats_dump(st);

    mu_assert(EQ(st->sumsq, expect.sumsq, 3), "sumsq not valid");
    mu_assert(EQ(st->sum, expect.sum, 3), "sum not valid");
    mu_assert(EQ(st->min, expect.min, 3), "min not valid");
    mu_assert(EQ(st->max, expect.max, 3), "max not valid");
    mu_assert(EQ(st->n, expect.n, 3), "quantity not valid");
    mu_assert(EQ(expect_mean, Stats_mean(st), 3), "mean not valid");
    mu_assert(EQ(expect_stddev, Stats_stddev(st), 3), "stddev not valid");

    return NULL;
}

char *test_recreate()
{
    Stats *st = Stats_recreate(
        expect.sum, expect.sumsq, expect.n, expect.min, expect.max);
    mu_assert(st->sum = expect.sum, "sum not equal");
    mu_assert(st->sumsq == expect.sumsq, "sumsq not equal");
    mu_assert(st->n == expect.n, "n not equal");
    mu_assert(st->max == expect.max, "max not equal");
    mu_assert(EQ(expect_mean, Stats_mean(st), 3), "mean not valid");
    mu_assert(EQ(expect_stddev, Stats_stddev(st), 3), "stddev not valid");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_operations);
    mu_run_test(test_recreate);

    return NULL;
}

RUN_TESTS(all_tests);