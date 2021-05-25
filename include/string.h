#ifndef STDC_STRING_H
#define STDC_STRING_H


#include <stdio.h>
#include <string.h>

#include "utf8.h"
#include "char.h"
#include "vector.h"


#define INITIAL_STRING_CAPACITY (64)

#define STRING_SIZE(self) (((String *) self)->size)
#define STRING_CAPACITY(self) (((String *) self)->array.member_count)

#define STRING_AS_PTR(self) ((uint8_t *) ((String *) self)->array.members)


typedef struct vector String;


String *string_with_capacity(String *self, size_t capacity);

String *string_new(String *self);

String *string_from_str(String *self, char *str);


bool string_empty(struct vector *self);

size_t string_size(String *self);

size_t string_capacity(String *self);

void string_clear(struct vector *self);

void string_free(struct vector *self);

/**
Iterate from back until it's not a continuation byte.
Removes the last character from the string buffer and returns it.
Returns None if this String is empty.
*/
Char string_pop(String *self);

void string_push(String *self, Char ch);

void string_push_str(String *self, char *str);

void string_push_strn(String *self, char *str, size_t size);

void string_extend(String *self, String *other);

uint8_t *string_as_ptr(String *self);

/**
Returns pointer to a NULL terminated string suitable for use as `char *`
Can be used with puts, printf, etc.
*/
char *string_as_str(String *self);


/// IO operations

/**
Reads in at most `count` characters from stream.
Reading stops after an EOF or a newline.
If a newline is read, it is stored into the string.
*/
void string_get(String *self, FILE *stream, size_t count);

void string_get_till(String *self, FILE *stream, size_t count, Char delimiter);

void string_put(String *self, FILE *stream);


#endif /* STDC_STRING_H */