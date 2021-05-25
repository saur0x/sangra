/**
gcc -Wall -o test test.c array.c
./test
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>


#include "array.h"



int main(void)
{
    int filler = 0xF;
    int new_filler = 0xA;
    int x_filler = 0x5;

    size_t member_size = sizeof(int);
    size_t member_count = 16;

    Array array;
    array_new(&array, member_size, member_count);

    // Search and replace &array with array
    // Array *array = array_new(NULL, member_size, member_count);

    assert(!array_empty(&array));
    assert(member_count == array_size(&array));

    array_fill(&array, &x_filler);
    for (size_t i = 0; i < array_size(&array); ++i)
        assert(x_filler == *(int *) array_get(&array, i));

    for (size_t i = 0; i < array_size(&array); ++i)
        printf("%d\n", *(int *) array_get(&array, i));
    putchar('\n');

    member_count = 4;
    array_resize(&array, member_count);

    assert(!array_empty(&array));
    assert(member_count == array_size(&array));

    array_set(&array, 0, &filler);
    assert(filler == *(int *) array_front(&array));

    for (size_t i = 0; i < array_size(&array); ++i)
        printf("%d\n", *(int *) array_get(&array, i));
    putchar('\n');

    array_set(&array, array_size(&array) - 1, &new_filler);
    assert(new_filler == *(int *) array_back(&array));

    for (size_t i = 0; i < array_size(&array); ++i)
        printf("%d\n", *(int *) array_get(&array, i));
    putchar('\n');

    array_set(&array, 1, &filler);
    assert(filler == *(int *) array_get(&array, 1));

    for (size_t i = 0; i < array_size(&array); ++i)
        printf("%d\n", *(int *) array_get(&array, i));
    putchar('\n');

    array_free(&array);
    assert(array_empty(&array));
}