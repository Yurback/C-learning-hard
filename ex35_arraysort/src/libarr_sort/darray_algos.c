#include <libarr_sort/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
    int mainindex = array->size - 1;
    int curindex = mainindex;
    int offset = 0;
    void **mainPt = array->contents;
    void **curPt = NULL;
    void **parentPt = NULL;
    void *tmpPt = NULL;

    while (mainindex > 0)
    {
        curindex = mainindex;
        while (curindex > 0)
        {
            curPt = mainPt + curindex;
            offset = (curindex - 1) / 2;
            parentPt = mainPt + offset;
            if (cmp(curPt, parentPt) > 0)
            {
                tmpPt = *curPt;
                *curPt = *parentPt;
                *parentPt = tmpPt;
            }
            curindex--;
        }
        tmpPt = *(mainPt + mainindex);
        *(mainPt + mainindex) = *mainPt;
        *mainPt = tmpPt;
        mainindex--;
    }

    return 0;
}

int mergesort(void **array, int size, size_t length, DArray_compare cmp)
{
    if (size == 0 || size == 1)
        return 0;
    if (size == 2)
    {
        void **cur = array;
        if (cmp(cur, cur + 1) > 0)
        {
            void *tmp = *cur;
            *cur = *(cur + 1);
            *(cur + 1) = tmp;
        }
        return 0;
    }
    int mid = size / 2;
    int leftsize = mid;
    int rightsize = size - mid;
    void **left = array;
    void **right = array + mid;
    mergesort(left, leftsize, sizeof(void *), cmp);
    mergesort(right, rightsize, sizeof(void *), cmp);
    void **copyarray = calloc(size, sizeof(void *));
    check_mem(copyarray);
    void **cur = copyarray;

    while (leftsize > 0 || rightsize > 0)
    {
        if (leftsize <= 0)
        {
            *(cur++) = *(right++);
            rightsize--;
            continue;
        }
        if (rightsize <= 0)
        {
            *(cur++) = *(left++);
            leftsize--;
            continue;
        }
        if (cmp(left, right) > 0)
        {
            *(cur++) = *(right++);
            rightsize--;
        }
        else
        {
            *(cur++) = *(left++);
            leftsize--;
        }
    }
    memcpy(array, copyarray, size * length);
    free(copyarray);
    return 0;
error:
    return 1;
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
    return mergesort(array->contents, DArray_count(array),
                     sizeof(void *), cmp);
}