#ifndef STDC_CHARS_H
#define STDC_CHARS_H

#include "utf8/utf8.h"
#include "char/char.h"
#include "string/string.h"
#include "iterator/iterator.h"


/**
An iterator over string that yields Char.
*/
typedef struct iterator Chars;

Chars *chars_new(Chars *self, String *string)
{
    if (!self)
        self = (Chars *) malloc(sizeof(Chars));
    
    *self = {
        .object = string,
        .start = STRING_AS_PTR(string),
        .current = STRING_AS_PTR(string),
        .index = 0,
        .offset = 0,
        .exhausted = 0
    };

    return self;
}

Char chars_next(Chars *self)
{
    if (self->current >= STRING_AS_PTR(self->object) + string_size(self->object)) {
        // EXCEPTION: Exhausted
        self->exhausted = 1;
        return CHAR_NULL;
    }

    Char c = char_read(self->current);
    self->current += UTF8_GET_COUNT(c);
    self->index++;
    return c;
}

size_t chars_count(Chars *self)
{
    size_t count = 0;
    // while (iterator_next(self)) count++;

    size_t size = string_size(self->object);
    while (self->current < STRING_AS_PTR(self->object) + size) {
        count += !UTF8_IS_CONTINUATION(* (uint8_t *) self->current);
    }

    return count;
}

Char chars_last(Chars *self)
{
    Char last;
    Char current;

    while (current = chars_next(self))
        last = current;

    return last;
}

Char chars_nth(Chars *self, size_t n)
{
    Char current;

    for (; n; --n) {
        current = chars_next(self);
        if (current == CHAR_NULL)
            return current;
    }

    current = chars_next(self);
    return current;
}

#endif /* STDC_CHARS_H */