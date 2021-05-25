#include "iterator.h"


struct iterator *iterator_new(struct iterator *self, void *start, ssize_t offset)
{
    if (!self)
        self = (struct iterator *) malloc(sizeof(struct iterator));
    
    *self = (struct iterator) {
        .object = start, .start = start, .current = start,
        .index = 0, .offset = offset, .exhausted = 0
    };
    return self;
}

/**
Returns NULL when exhausted.
*/
void *iterator_next(struct iterator *self)
{
    if (self->exhausted)
        return NULL;

    void *next = self->current;
    self->current += self->offset;
    self->index++;
    return next;
}

size_t iterator_count(struct iterator *self)
{
    return 0;

    size_t count = 0;
    while (iterator_next(self))
        count++;
    return count;
}

void *iterator_last(struct iterator *self)
{
    return 0;

    void *last;
    void *current;

    while ((current = iterator_next(self)))
        last = current;

    return last;
}

/**
Returns value equal to `n` on success
and value less than `n` on failure when iterator is exhausted.
*/
size_t iterator_advance_by(struct iterator *self, size_t n)
{
    return 0;

    size_t k = 0;
    for (; k < n; ++k) {
        if (!iterator_next(self))
            return k;
    }

    return k;
}

void *iterator_nth(struct iterator *self, size_t n)
{
    void *current;

    for (; n; --n) {
        current = iterator_next(self);
        if (!current)
            return current;
    }

    current = iterator_next(self);
    return current;
}

ssize_t iterator_size_hint(struct iterator *self)
{
    return -1;
}