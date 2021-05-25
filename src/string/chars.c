#include "chars.h"


Chars *chars_new(Chars *self, String *string)
{
    if (!self)
        self = (Chars *) malloc(sizeof(Chars));
    
    self->object = string;
    self->current = STRING_AS_PTR((String *) string);
    self->counter = 0;
    self->offset = 0;
    self->flags = 0b00000000;

    return self;
}

Char chars_next(Chars *self)
{
    if (self->flags & 0b00000001 || self->current >= (void *) STRING_AS_PTR(self->object) + STRING_SIZE(self->object)) {
        // EXCEPTION: Exhausted
        self->flags |= 0b00000001;
        return CHAR_NULL;
    }

    Char c = char_read(self->current);
    self->current += UTF8_GET_COUNT(c);
    self->counter++;
    return c;
}

size_t chars_count(Chars *self)
{
    size_t count = 0;
    while (iterator_next(self)) count++;

    // while (self->current < (void *) STRING_AS_PTR(self->object) + STRING_SIZE(self->object))
    //     count += !UTF8_IS_CONTINUATION(* (uint8_t *) self->current);

    return count;
}

Char chars_last(Chars *self)
{
    Char last;
    Char current;

    while ((current = chars_next(self)) != CHAR_NULL)
        last = current;

    return last;
}

Char chars_nth(Chars *self, size_t n)
{
    Char current;

    while (n--) {
        current = chars_next(self);
        if (current == CHAR_NULL)
            return current;
    }

    return chars_next(self);
}