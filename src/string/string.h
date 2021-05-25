#ifndef STDC_STRING_H
#define STDC_STRING_H


#include <stdio.h>

#include "vector/vector.h"
#include "char/char.h"
#include "utf8/utf8.h"


#define BYTE_TYPE uint8_t
#define BYTE_SIZE (1)

#define STRING_AS_PTR(self) ((uint8_t *) self->array.members)

typedef struct vector String;


String *string_with_capacity(String *self, size_t capacity)
{
    return vector_with_capacity(self, BYTE_SIZE, capacity);
}

String *string_new(String *self)
{
    return vector_new(self, BYTE_SIZE);
}


/*
uint8_t string_get(String *self, size_t index)
{
    return *(uint8_t *) vector_get(self, index);
}


void string_set(String *self, size_t index, uint8_t byte)
{
    vector_set(self, index, &byte);
}
*/


bool string_empty(struct vector *self)
{
	return !VECTOR_SIZE(self);
}

size_t string_size(String *self)
{
    return VECTOR_SIZE(self);
    // return vector_size(self);
}

size_t string_capacity(String *self)
{
    return VECTOR_CAPACITY(self);
    // return vector_capacity(self);
}

void string_free(struct vector *self) {
    vector_free(self);
}

/**
Iterate from back until it's not a continuation byte.
Removes the last character from the string buffer and returns it.
Returns None if this String is empty.
*/
Char string_pop(String *self)
{
    size_t size = VECTOR_SIZE(self);
    if (!size)
        return CHAR_NULL;

    Char ch = char_read_back(vector_get(self, size - 1));
    uint8_t count = UTF8_GET_COUNT(ch);

    if (count > size)
        return CHAR_NULL;
    
    size -= count;
    vector_resize(self, size, NULL);

    return ch;
}

void string_push(String *self, Char ch)
{
    char byte_array[4] = { 0 };
    uint8_t count = UTF8_GET_COUNT(ch);

    vector_reserve_additional(self, count);

    char_write(ch, byte_array);

    for (size_t i = 0; i < count; ++i)
        vector_push(self, byte_array + i);
}

void string_push_str(String *self, char *str, size_t size)
{
    for (size_t i = 0; i < size && str[i]; ++i)
        vector_push(self, str + i);
}

void string_extend(String *self, String *other)
{
    vector_extend(self, other);
}

uint8_t *string_as_ptr(String *self)
{
    return (uint8_t *) self->array.members;
}

/**
Returns pointer to a NULL terminated string suitable for use as `char *`
*/
char *string_as_str(String *self)
{
    vector_reserve_additional(self, 1);

    // UNSAFE
    // * (uint8_t *) self->array.members[VECTOR_SIZE(self)] = 0;

    // SLOW
    uint8_t zero = 0;
    array_set(&self->array, VECTOR_SIZE(self), &zero);

    return (char *) self->array.members;
}


/// IO operations

/**
Reads in at most `count` characters from stream.
Reading stops after an EOF or a newline.
If a newline is read, it is stored into the string.
*/
void string_get(String *self, FILE *stream, size_t count)
{
    Char ch;
    while (!feof(stream) && count--) {
        ch = char_get(stream);
        string_push(self, ch);
    }
}

void string_get_till(String *self, FILE *stream, size_t count, Char delimiter)
{
    Char ch;
    while (!feof(stream) && count--) {
        ch = char_get(stream);
        if (ch == delimiter)
            break;
        string_push(self, ch);
    }
}

void string_put(String *self, FILE *stream)
{
    fwrite(string_as_ptr(self), 1, string_size(self), stream);
}


#endif /* STDC_STRING_H */