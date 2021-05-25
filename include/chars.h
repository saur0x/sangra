#ifndef STDC_CHARS_H
#define STDC_CHARS_H

#include "utf8.h"
#include "char.h"
#include "string.h"
#include "iterator.h"


/**
An iterator over string that yields Char.
*/
typedef struct iterator Chars;

Chars *chars_new(Chars *self, String *string);

Char chars_next(Chars *self);

size_t chars_count(Chars *self);

Char chars_last(Chars *self);

Char chars_nth(Chars *self, size_t n);


#endif /* STDC_CHARS_H */