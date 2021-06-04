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

        string_push_str(string, st);

        assert(!string_empty(string));
        assert(string_size(string) == st_size + size);

        string_put(string, stdout);
        char_put('\n', stdout);

        for (ssize_t i = st_size - 1; i >= 0; --i)
            char_put(string_pop(string), stderr);

        assert(string_empty(string));
        assert(string_size(string) == size);
    }

    #ifndef AUTOMATIC_TESTING
    {
        string_get_till(string, stdin, 10, '\n');
        char_put('|', stdout);
        string_put(string, stdout);
        char_put('|', stdout);
        printf("%s", string_as_str(string));
        char_put('|', stdout);
        char_put('\n', stdout);
        string_clear(string);
    }
    #endif

    {
        printf("%lu\t%lu\n", string_size(string), string_capacity(string));
    }

    string_free(string);
    assert(string_empty(string));

    free(string);
}