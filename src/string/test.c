/**
gcc -Wall -I ../../src -o test test.c ../vector/vector.c ../array/array.c ../char/char.c ../utf8/utf8.c
./test
echo -n '😳न' | ./test
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>


#include "string.h"



int main(void)
{
    size_t member_size = sizeof(int);
    size_t member_count = 16;
    size_t capacity = 1;

    String *string = string_with_capacity(NULL, capacity);
    assert(string_empty(string));
    assert(string_capacity(string) == capacity);

    {
        char st[] = "Hello, World!";
        size_t st_size = strlen(st);

        size_t size = string_size(string);

        for (size_t i = 0; i < st_size; ++i)
            string_push(string, st[i]);

        assert(!string_empty(string));
        assert(string_size(string) == st_size + size);

        for (ssize_t i = st_size - 1; i >= 0; --i)
            assert(string_pop(string) == st[i]);
        
        assert(string_empty(string));
        assert(string_size(string) == size);
    }

    {
        char st[] = "नमस्ते";
        size_t st_size = strlen(st);

        size_t size = string_size(string);

        string_push_str(string, st, st_size);

        assert(!string_empty(string));
        assert(string_size(string) == st_size + size);

        string_put(string, stdout);
        putchar('\n');

        for (ssize_t i = st_size - 1; i >= 0; --i)
            char_put(string_pop(string), stderr);

        assert(string_empty(string));
        assert(string_size(string) == size);
    }

    {
        string_get_till(string, stdin, 10, '\n');
        putchar('|');
        string_put(string, stdout);
        putchar('|');
        vector_truncate(string, 0);
    }

    {
        printf("%lu\t%lu\n", string_size(string), string_capacity(string));
    }

    

    // vector_push(vector, &filler);
    // assert(filler == *(int *) vector_front(vector));
    // assert(!vector_empty(vector));

    // vector_push(vector, &filler);
    // assert(filler == *(int *) vector_get(vector, 1));

    // vector_push(vector, &filler);
    // vector_set(vector, vector_size(vector) - 1, &new_filler);
    // assert(new_filler == *(int *) vector_back(vector));

    // vector_resize(vector, 12, &x_filler);
    // assert(vector_size(vector) == 12);

    // capacity = vector_capacity(vector);
    // vector_resize_capacity(vector, capacity + 10);
    // assert(vector_capacity(vector) == capacity + 10);

    // capacity = 32;
    // vector_reserve(vector, capacity);
    // assert(vector_capacity(vector) == capacity);

    // capacity = vector_size(vector);
    // shrink_to_fit(vector);
    // assert(vector_capacity(vector) == capacity);

    // vector_insert(vector, 1, &ff);
    // assert(ff == *(int *) vector_get(vector, 1));

    // int back = vector_size(vector) - 1;
    // vector_insert(vector, back, &ff);
    // assert(ff == *(int *) vector_get(vector, back));

    // vector_pop(vector);

    // assert(ff == *(int *) vector_back(vector));

    // member_count = vector_size(vector) - 1;
    // vector_remove(vector, 2);
    // assert(vector_size(vector) == member_count);

    // capacity = 64;
    // int delta_capacity = capacity - vector_size(vector);
    // vector_reserve_additional(vector, delta_capacity);
    // assert(vector_capacity(vector) == capacity);

    // vector_truncate(vector, 5);
    // assert(vector_size(vector) == 5);

    // for (size_t i = 0; i < vector_size(vector); ++i)
    //     printf("%d\n", *(int *) vector_get(vector, i));
    // printf("Size: %lu\tCapacity: %lu\n", vector_size(vector), vector_capacity(vector));
    // putchar('\n');

    string_free(string);
    assert(string_empty(string));

    free(string);
}