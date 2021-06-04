#include "exception.h"


struct exception_stack *exception_stack_push(struct exception_stack *previous)
{
	struct exception_stack *self = (struct exception_stack *) malloc(sizeof(struct exception_stack));
	self->previous = previous;
	self->flags = 0x00;
	return self;
}

struct exception_stack *exception_stack_pop(struct exception_stack *self)
{
	struct exception_stack *previous = self;

	if (self) {
		previous = self->previous;
		free(self);
	}

	return previous;
}


struct exception_stack *exception_stack_push_front(struct exception_stack *self)
{
	struct exception_stack *new_front = exception_stack_push(NULL);
	struct exception_stack *front = self;

	if (front) {
		while (front->previous)
			front = front->previous;
		front->previous = new_front;
	}

	return new_front;
}


struct exception_stack *exception_stack_pop_front(struct exception_stack *self)
{
	struct exception_stack *front = self;
	struct exception_stack *new_front = NULL;

	if (front) {
		while (front->previous) {
			new_front = front;
			front = front->previous;
		}

		free(front);

		if (new_front) {
			new_front->previous = NULL;
			return new_front;
		}
	}

	return NULL;
}


void exception_stack_free(struct exception_stack *self)
{
	struct exception_stack *current = self;
	struct exception_stack *previous;

	while (current) {
		previous = current->previous;
		free(current);
		current = previous;
	}
}


size_t exception_stack_depth(struct exception_stack *self)
{
	struct exception_stack *current = self;
	size_t counter = 0;
	for (; current; counter++, current = current->previous);
	return counter;
}


uint8_t exception_stack_flag_get(struct exception_stack *self, uint8_t flag)
{
	if (self) {
		return self->flags & flag;
	}

	return 0;
}

uint8_t exception_stack_flag_set(struct exception_stack *self, uint8_t flag)
{
	if (self) {
		self->flags |= flag;
	}

	return self != NULL;
}