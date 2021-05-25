#ifndef STDC_VECTOR_H
#define STDC_VECTOR_H


#include "array.h"


#define INITIAL_VECTOR_CAPACITY (64)

#define VECTOR_SIZE(SELF) (SELF->size)
#define VECTOR_CAPACITY(SELF) (SELF->array.member_count)


struct vector
{
	struct array array;
	size_t size;
};

typedef struct vector Vector;


struct vector *vector_with_capacity(struct vector *self, size_t member_size, size_t capacity);


struct vector *vector_new(struct vector *self, size_t member_size);


/// Element access

void *vector_get(struct vector *self, size_t index);


void vector_set(struct vector *self, size_t index, void *value);


void *vector_front(struct vector *self);


void *vector_back(struct vector *self);


/// Capacity

void vector_auto_resize(struct vector *self);


void vector_resize(struct vector *self, size_t size, void *value);


void vector_resize_capacity(struct vector *self, size_t capacity);


bool vector_empty(struct vector *self);


size_t vector_size(struct vector *self);


size_t vector_capacity(struct vector *self);


/**
Increase the capacity of the vector to a value greater or equal to `capacity`.
If `capacity` is greater than the current capacity(),
new storage is allocated, otherwise the method does nothing. 
*/
void vector_reserve(struct vector *self, size_t capacity);


void shrink_to_fit(struct vector *self);


/// Modifiers

void vector_clear(struct vector *self);


void vector_free(struct vector *self);


void vector_insert(struct vector *self, size_t index, void *value);


void vector_push(struct vector *self, void *value);


/**
Removes the last element of the container.
Calling `vector_pop` on an empty container does nothing.
*/
void vector_pop(struct vector *self);

void vector_extend(struct vector *self, struct vector *other);


void vector_remove(struct vector *self, size_t index);


void vector_reserve_additional(struct vector *self, size_t additional);


void vector_truncate(struct vector *self, size_t size);


#endif /* STDC_VECTOR_H */