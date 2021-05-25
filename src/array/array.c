#include "array.h"


struct array *array_new(struct array *self, size_t member_size, size_t member_count)
{
	if (!self)
		self = (struct array *) malloc(sizeof(struct array));
	
	*self = (struct array) {
		.members = malloc(member_count * member_size),
		.member_count = member_count,
		.member_size = member_size
	};

	return self;
}


void *array_get(struct array *self, size_t position)
{
	if (position >= self->member_count)
		return NULL;

	return self->members + position * self->member_size;
}


void array_set(struct array *self, size_t position, void *value)
{
	if (position >= self->member_count)
		return;

	memcpy(self->members + position * self->member_size, value, self->member_size);
}


void *array_front(struct array *self)
{
	return array_get(self, 0);
}


void *array_back(struct array *self)
{
	return array_get(self, self->member_count - 1);
}


bool array_empty(struct array *self)
{
	return (self->member_count == 0);
}


size_t array_size(struct array *self)
{
	return self->member_count;
}


void array_fill(struct array *self, void *value)
{
	for (size_t i = 0; i < self->member_count; ++i)
		array_set(self, i, value);
}


void array_resize(struct array *self, size_t count)
{
	self->member_count = count;
	self->members = realloc(self->members, self->member_count * self->member_size);
}


void array_clear(struct array *self)
{
}

void array_free(struct array *self)
{
	if (self) {
		if (self->members)
			free(self->members);

		*self = (struct array) {
			.members = NULL,
			.member_count = 0,
			.member_size = 0
		};
	}
}