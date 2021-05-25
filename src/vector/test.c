/**
gcc -Wall -o test test.c vector.c ../array/array.c -I ../../src
./test
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>


#include "vector.h"



int main(void)
{
    int filler = 0xF;
    int new_filler = 0xA;
    int x_filler = 0x5;
    int ff = 0xFFFF;

    size_t member_size = sizeof(int);
    size_t member_count = 16;
    size_t capacity = 1;

    Vector *vector = vector_with_capacity(NULL, member_size, capacity);

    assert(vector_capacity(vector) == capacity);

    vector_push(vector, &filler);
    assert(filler == *(int *) vector_front(vector));
    assert(!vector_empty(vector));

    vector_push(vector, &filler);
    assert(filler == *(int *) vector_get(vector, 1));

    vector_push(vector, &filler);
    vector_set(vector, vector_size(vector) - 1, &new_filler);
    assert(new_filler == *(int *) vector_back(vector));

    vector_resize(vector, 12, &x_filler);
    assert(vector_size(vector) == 12);

    capacity = vector_capacity(vector);
    vector_resize_capacity(vector, capacity + 10);
    assert(vector_capacity(vector) == capacity + 10);

    capacity = 32;
    vector_reserve(vector, capacity);
    assert(vector_capacity(vector) == capacity);

    capacity = vector_size(vector);
    shrink_to_fit(vector);
    assert(vector_capacity(vector) == capacity);

    vector_insert(vector, 1, &ff);
    assert(ff == *(int *) vector_get(vector, 1));

    int back = vector_size(vector) - 1;
    vector_insert(vector, back, &ff);
    assert(ff == *(int *) vector_get(vector, back));

    vector_pop(vector);

    assert(ff == *(int *) vector_back(vector));

    member_count = vector_size(vector) - 1;
    vector_remove(vector, 2);
    assert(vector_size(vector) == member_count);

    capacity = 64;
    int delta_capacity = capacity - vector_size(vector);
    vector_reserve_additional(vector, delta_capacity);
    assert(vector_capacity(vector) == capacity);

    vector_truncate(vector, 5);
    assert(vector_size(vector) == 5);

    for (size_t i = 0; i < vector_size(vector); ++i)
        printf("%d\n", *(int *) vector_get(vector, i));
    printf("Size: %lu\tCapacity: %lu\n", vector_size(vector), vector_capacity(vector));
    putchar('\n');

    vector_free(vector);
    assert(vector_empty(vector));

    free(vector);
}