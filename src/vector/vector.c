#include "vector.h"


struct vector *vector_with_capacity(struct vector *self, size_t member_size, size_t capacity)
{
	if (!self)
		self = (struct vector *) malloc(sizeof(struct vector));

	array_new(&self->array, member_size, capacity);
	self->size = 0;
	return self;
}

struct vector *vector_new(struct vector *self, size_t member_size)
{
	return vector_with_capacity(self, member_size, INITIAL_VECTOR_CAPACITY);
}


void *vector_get(struct vector *self, size_t index)
{
	if (index >= VECTOR_SIZE(self))
		return NULL;
	return array_get(&self->array, index);
}


void vector_set(struct vector *self, size_t index, void *value)
{
	if (index >= VECTOR_SIZE(self))
		return;
	array_set(&self->array, index, value);
}


void *vector_front(struct vector *self)
{
	return vector_get(self, 0);
}


void *vector_back(struct vector *self)
{
	return vector_get(self, VECTOR_SIZE(self) - 1);
}


void vector_auto_resize(struct vector *self)
{
	size_t capacity = VECTOR_CAPACITY(self);

	if (capacity <= VECTOR_SIZE(self))
		array_resize(&self->array, capacity ? 2 * capacity : INITIAL_VECTOR_CAPACITY);
}


void vector_resize(struct vector *self, size_t size, void *value)
{
	if (size <= self->size) {
		self->size = size;
		return;
	}

	for (size_t i = self->size; i < size; ++i)
		vector_push(self, value);
}


void vector_resize_capacity(struct vector *self, size_t capacity)
{
	if (capacity != vector_capacity(self))
		array_resize(&self->array, capacity);
}


bool vector_empty(struct vector *self)
{
	return !VECTOR_SIZE(self);
}


size_t vector_size(struct vector *self)
{
	return self->size;
}


size_t vector_capacity(struct vector *self)
{
	return self->array.member_count;
}


void vector_reserve(struct vector *self, size_t capacity)
{
	if (capacity > self->array.member_count)
		vector_resize_capacity(self, capacity);
}


void shrink_to_fit(struct vector *self)
{
	size_t size = vector_size(self);
	size_t capacity = vector_capacity(self);

	if (capacity > size)
		vector_resize_capacity(self, size);
}


void vector_clear(struct vector *self)
{
	self->size = 0;
}

void vector_free(struct vector *self)
{
	array_free(&self->array);
	self->size = 0;
}


/**
Panics if index >= size.
*/
void vector_insert(struct vector *self, size_t index, void *value)
{
	if (index >= VECTOR_SIZE(self)) {
		// EXCEPTION: index cannot be >= size
		return;
	}

	vector_auto_resize(self);

	self->size++;

	for (ssize_t i = VECTOR_SIZE(self) - 1; i >= index; --i)
		vector_set(self, i + 1, vector_get(self, i));

	vector_set(self, index, value);
}


void vector_push(struct vector *self, void *value)
{
	vector_auto_resize(self);
	self->size++;
	array_set(&self->array, VECTOR_SIZE(self) - 1, value);
}


void vector_pop(struct vector *self)
{
	if (VECTOR_SIZE(self)) {
		// vector_resize(self, VECTOR_SIZE(self) - 1);
		self->size--;
	}
}


/// Rust functionality
/*
void vector_append_vector(struct vector *self, struct vector *other)
{
	
}

size_t vector_len(struct vector *self)
{
	return self->size;
}

bool vector_is_empty(struct vector *self)
{
	return self->size != 0;
}
*/

void vector_extend(struct vector *self, struct vector *other)
{
	size_t other_size = VECTOR_SIZE(other);
	for (size_t i = 0; i < other_size; ++i)
		vector_push(self, vector_get(other, i));
}

void vector_remove(struct vector *self, size_t index)
{
	for (size_t i = index; i < VECTOR_SIZE(self) - 1; ++i) {
		vector_set(self, i, vector_get(self, i + 1));
	}

	self->size--;
}

void vector_reserve_additional(struct vector *self, size_t additional)
{
	vector_reserve(self, VECTOR_SIZE(self) + additional);
}

void vector_truncate(struct vector *self, size_t size)
{
	if (size < VECTOR_SIZE(self))
		self->size = size;
}
