/*
  * Based on code by Andre Reinald then heavily modified by Zed A. Shaw.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <libarr_sort/radixmap.h>
#include <lcthw/dbg.h>

RadixMap *RadixMap_create(size_t max)
{
    RadixMap *map = calloc(1, sizeof(RadixMap));
    check_mem(map);

    map->contents = calloc(max, sizeof(RMElement));
    check_mem(map->contents);

    map->temp = calloc(max, sizeof(RMElement));
    check_mem(map->temp);

    map->max = max;
    map->size = 0;

    return map;
error:
    if (map)
    {
        if (map->contents)
            free(map->contents);
        if (map->temp)
            free(map->temp);
        free(map);
    }
    return NULL;
}

void RadixMap_destroy(RadixMap *map)
{
    if (map)
    {
        free(map->contents);
        free(map->temp);
        free(map);
    }
}

#define ByteOf(x, y) (((uint8_t *)x)[(y)])

static inline void radix_sort(short offset, uint64_t max,
                              uint64_t *source, uint64_t *dest)
{
    uint64_t count[256] = {0};
    uint64_t *cp = NULL;
    uint64_t *sp = NULL;
    uint64_t *size = NULL;
    uint64_t s = 0;
    uint64_t c = 0;

    // Ref radixmap.png (LOOP 1/ LOOP 2/ LOOP3)

    // count occurences of every byte value
    for (sp = source, size = source + max; sp < size; sp++)
    {
        count[ByteOf(sp, offset)]++;
    }

    // transform count into index by summing
    // elements and storing into same array
    for (s = 0, cp = count, size = count + 256; cp < size; cp++)
    {
        c = *cp;
        *cp = s;
        s += c;
    }

    // fill dest with the right values in the right place
    for (sp = source, size = source + max; sp < size; sp++)
    {
        cp = count + ByteOf(sp, offset);
        dest[*cp] = *sp;
        ++(*cp);
    }
}

void RadixMap_sort(RadixMap *map)
{
    uint64_t *source = &map->contents[0].raw;
    uint64_t *temp = &map->temp[0].raw;

    radix_sort(0, map->size, source, temp);
    radix_sort(1, map->size, temp, source);
    radix_sort(2, map->size, source, temp);
    radix_sort(3, map->size, temp, source);
}

RMElement *RadixMap_find(RadixMap *map, uint32_t to_find)
{
    int low = 0;
    int high = map->size - 1;
    RMElement *data = map->contents;

    while (low <= high)
    {
        int middle = low + (high - low) / 2;
        uint32_t key = data[middle].data.key;

        if (to_find < key)
        {
            high = middle - 1;
        }
        else if (to_find > key)
        {
            low = middle + 1;
        }
        else
        {
            return &data[middle];
        }
    }

    return NULL;
}

int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value)
{
    check(key < UINT32_MAX, "Key can't be equal to UINT32_MAX.");

    RMElement element = {.data = {.key = key, .value = value}};
    check(map->size < map->max, "RadixMap is full.");

    map->contents[map->size++] = element;

    RadixMap_sort(map);

    return 0;

error:
    return -1;
}

int RadixMap_delete(RadixMap *map, RMElement *el)
{
    check(map->size > 0, "There is nothing to delete.");
    check(el != NULL, "Can't delete a NULL element.");

    el->data.key = UINT32_MAX;

    if (map->size > 1)
    {
        // don't bother resorting a map of 1 length
        RadixMap_sort(map);
    }

    map->size--;

    return 0;
error:
    return -1;
}

int RadixMap_display(RadixMap *map, char mode)
{
    if (mode == 'a')
    {
        printf("=============Radimax_info==============\n");
        UPTO((int)map->max)
        {
            printf("Element: %d ; Key: %u ; Value : %u \n", i, map->contents[i].data.key, map->contents[i].data.value);
        }
        printf("=======================================\n");
    }
    else
    {
        printf("=============Radimax_info==============\n");
        UPTO((int)map->size)
        {
            printf("Element: %d ; Key: %u ; Value : %u \n", i, map->contents[i].data.key, map->contents[i].data.value);
        }
        printf("=======================================\n");
    }
    return 0;
}