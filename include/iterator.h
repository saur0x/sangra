#ifndef STDC_ITERATOR_H
#define STDC_ITERATOR_H


#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>


struct iterator
{
    /// Pointer to the underlying object. It may be needed for other iterators.
    void *object;

    /// Current position of the iterator.
    void *current;

    /// `counter` for the number of times next has been called.
    size_t counter;

    /// `offset` between elements of iterator / container.
    /// Negative if reverse iterator, and zero if the elements aren't same size.
    ssize_t offset;

    /// 0th: if exhausted
    uint8_t flags;
};

typedef struct iterator Iterator;

struct iterator *iterator_new(struct iterator *self, void *start, ssize_t offset);

/**
Returns NULL when exhausted.
*/
void *iterator_next(struct iterator *self);

void *iterator_nth(struct iterator *self, size_t n);


#endif  /* STDC_ITERATOR_H */