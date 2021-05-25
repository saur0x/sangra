#ifndef STDC_ARRAY_H
#define STDC_ARRAY_H


#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


struct array
{
	void *members;
	size_t member_count;
	size_t member_size;
};

typedef struct array Array;


struct array *array_new(struct array *self, size_t member_size, size_t member_count);


/// Element Access

/**
# `void *array_get(struct array *self, size_t position);`
Returns a `void pointer` to the element at specified `position`, with bounds checking.
If position is not within the range of the array, `NULL` is returned.

# Parameters
- self
	- Pointer to `struct array`
- position
	- Position of the element to return

# Return
`void pointer` to the requested element

# Complexity
Constant

# Example
```c
array_at(array, 4)
```
*/
void *array_get(struct array *self, size_t position);


void array_set(struct array *self, size_t position, void *value);


void *array_front(struct array *self);


/**
# `void *array_back(struct array *self)`

# Parameters
- self
	- Pointer to `struct array`

# Return
Returns a `void pointer` to the last element in the array.

# Complexity
Constant

# Notes
Calling back on an empty array returns `NULL`.

# Example
*/
void *array_back(struct array *self);


bool array_empty(struct array *self);


size_t array_size(struct array *self);


/// Operations

/**
Assigns the given value `value` to all elements in the container. 
*/
void array_fill(struct array *self, void *value);


/**
Resize the array to provided `size`.
*/
void array_resize(struct array *self, size_t count);


void array_clear(struct array *self);


void array_free(struct array *self);


#endif /* STDC_ARRAY_H */