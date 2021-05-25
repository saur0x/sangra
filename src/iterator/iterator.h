#ifndef STDC_ITERATOR_H
#define STDC_ITERATOR_H


#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>


struct iterator
{
    void *object;
    void *start;
    void *current;
    size_t index;
    ssize_t offset;
    uint8_t exhausted;
};

typedef struct iterator Iterator;

struct iterator *iterator_new(struct iterator *self, void *start, ssize_t offset);

/**
Returns NULL when exhausted.
*/
void *iterator_next(struct iterator *self);

// size_t iterator_count(struct iterator *self);

// void *iterator_last(struct iterator *self);

/**
Returns value equal to `n` on success
and value less than `n` on failure when iterator is exhausted.
*/
// size_t iterator_advance_by(struct iterator *self, size_t n);

void *iterator_nth(struct iterator *self, size_t n);

// ssize_t iterator_size_hint(struct iterator *self);


#endif  /* STDC_ITERATOR_H */