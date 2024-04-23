#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// count n times instead for-loop
#define UPTO(n) for (int i = 0; i < (n); i++)

// find length array
#define SIZE_ARR(arr) sizeof(arr) / sizeof(arr[0])

// DEBUG STATEMENTS if not define NDEBUG
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", \
                              __FILE__, __LINE__, ##__VA_ARGS__)
                              
#define PRINT_int(x) printf(#x " is %d\n", x)

#define PRINT_ld(x) printf(#x " is %ld\n", x)

#define PRINT_f(x) printf(#x " is %f\n", x)

#define PRINT_s(x) printf(#x " is %s\n", x)

#define PRINT_p(x) printf(#x " is %p\n", x)
#endif
// Logging extra information
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr,                                                   \
                                "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, \
                                clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,                              \
                                 "[WARN] (%s:%d: errno: %s) " M "\n", \
                                 __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", \
                                 __FILE__, __LINE__, ##__VA_ARGS__)

// Checking and seting sentinel
#define check(A, M, ...)           \
    if (!(A))                      \
    {                              \
        log_err(M, ##__VA_ARGS__); \
        errno = 0;                 \
        goto error;                \
    }

#define sentinel(M, ...)           \
    {                              \
        log_err(M, ##__VA_ARGS__); \
        errno = 0;                 \
        goto error;                \
    }

// Check memory allocation
#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...)   \
    if (!(A))                    \
    {                            \
        debug(M, ##__VA_ARGS__); \
        errno = 0;               \
        goto error;              \
    }

// QSORT MACROS : prefix in {order, reverse}
#define DECLARESORT(type)                                               \
	static int order##_##type##_compare(const void *a, const void *b)   \
	{                                                                   \
		const type aa = *(const type *)a;                               \
		const type bb = *(const type *)b;                               \
		return aa - bb;                                                 \
	}                                                                   \
	static int reverse##_##type##_compare(const void *a, const void *b) \
                                                                        \
	{                                                                   \
		const type *aa = a;                                             \
		const type *bb = b;                                             \
		return bb - aa;                                                 \
	}                                                                   \
	void order##_##type##_sort(type *a, int n)                          \
	{                                                                   \
		qsort(a, n, sizeof(type), order##_##type##_compare);            \
	}                                                                   \
	void reverse##_##type##_sort(type *a, int n)                        \
	{                                                                   \
		qsort(a, n, sizeof(type), reverse##_##type##_compare);          \
	}

#endif
