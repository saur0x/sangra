/**
gcc -Wall -I ../../src -o test test.c ../vector/vector.c ../array/array.c iterator.c
./test
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "iterator.h"
#include "vector.h"


int main(void)
{
    int filler = 0xF;
    int new_filler = 0xA;
    int x_filler = 0x5;
    int ff = 0xFFFF;

    size_t member_size = sizeof(int);
    size_t member_count = 12;
    size_t capacity = 1;

    Vector *vector = vector_with_capacity(NULL, member_size, capacity);

    assert(vector_capacity(vector) == capacity);

    for (int i = 0; i < member_count; ++i)
        vector_push(vector, &i);

    for (int i = 0; i < member_count; ++i) {
        printf("%d\n", *(int *) vector_get(vector, i));
    }

    putchar('\n');
    printf("%lu\t%lu\n", vector_size(vector), vector_capacity(vector));

    {
        Iterator *it = iterator_new(NULL, vector->array.members, member_size);
        assert(*(int *) iterator_next(it) == 0);
        assert(*(int *) iterator_next(it) == 1);
        free(it);
    }

    {
        Iterator *it = iterator_new(NULL, vector->array.members, member_size);
        assert(*(int *) iterator_nth(it, 3) == 3);
        assert(*(int *) iterator_nth(it, 4) == 8);
        free(it);
    }

    printf("%lu\t%lu\n", vector_size(vector), vector_capacity(vector));

    vector_free(vector);
    free(vector);
}