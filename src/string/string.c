#include "string.h"


String *string_with_capacity(String *self, size_t capacity)
{
    return vector_with_capacity(self, 1, capacity);
}

String *string_new(String *self)
{
    return string_with_capacity(self, INITIAL_STRING_CAPACITY);
}

String *string_from_str(String *self, char *str)
{
    size_t capacity = 0;
    for (; str[capacity]; ++capacity);
    
    if (!self)
        self = string_with_capacity(self, capacity);
    else
        vector_resize_capacity(self, capacity);

    memcpy(self->array.members, str, capacity);
    self->size = capacity;

    return self;
}


bool string_empty(struct vector *self)
{
	return !VECTOR_SIZE(self);
}

size_t string_size(String *self)
{
    // return vector_size(self);
    return STRING_SIZE(self);
}

size_t string_capacity(String *self)
{
    // return vector_capacity(self);
    return STRING_CAPACITY(self);
}

void string_clear(struct vector *self)
{
	self->size = 0;
}

void string_free(struct vector *self) {
    vector_free(self);
}


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

void string_push_str(String *self, char *str)
{
    for (size_t i = 0; str[i]; ++i)
        vector_push(self, str + i);
}

void string_push_strn(String *self, char *str, size_t size)
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

char *string_as_str(String *self)
{
    vector_reserve_additional(self, 1);

    // UNSAFE
    ((uint8_t *) self->array.members)[VECTOR_SIZE(self)] = 0;

    return (char *) self->array.members;
}


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
    fwrite(string_as_ptr(self), 1, STRING_SIZE(self), stream);
}