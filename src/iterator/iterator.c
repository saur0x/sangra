#include "iterator.h"


struct iterator *iterator_new(struct iterator *self, void *start, ssize_t offset)
{
    if (!self)
        self = (struct iterator *) malloc(sizeof(struct iterator));
    
    self->current = start;
    self->counter = 0;
    self->offset = offset;
    self->flags = 0b00000000;

    return self;
}

/**
Returns NULL when exhausted.
*/
void *iterator_next(struct iterator *self)
{
    if (self->flags & 0b00000001) {
        // self->flags |= 0b00000001;
        return NULL;
    }

    void *next = self->current;
    self->current += self->offset;
    self->counter++;
    return next;
}

size_t iterator_count(struct iterator *self)
{
    size_t count = 0;
    while (iterator_next(self))
        count++;
    return count;
}

void *iterator_last(struct iterator *self)
{
    void *current, *last;

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

    while (n--) {
        current = iterator_next(self);
        if (!current)
            return current;
    }

    return iterator_next(self);
}

/**
Negative if size couldn't be known.
*/
ssize_t iterator_size_hint(struct iterator *self)
{
    return -1;
}