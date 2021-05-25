#ifndef STDC_CHAR_H
#define STDC_CHAR_H


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "utf8.h"

#define CHAR_NULL (-1)

typedef uint32_t Char;



/// Rust functionality
/// TODO: Encoding, decoding from utf8 and utf16 and escape functions.

Char char_from_digit(uint32_t num, uint32_t radix);

bool char_is_digit(Char self, uint32_t radix);

uint32_t char_to_digit(Char self, uint32_t radix);


/// ASCII functions

bool char_eq_ignore_ascii_case(Char self, Char other);

bool char_is_ascii(Char self);

bool char_is_ascii_alphabetic(Char self);

bool char_is_ascii_alphanumeric(Char self);

bool char_is_ascii_control(Char self);

bool char_is_ascii_digit(Char self);

bool char_is_ascii_graphic(Char self);

bool char_is_ascii_hexdigit(Char self);

bool char_is_ascii_lowercase(Char self);

bool char_is_ascii_punctuation(Char self);

bool char_is_ascii_uppercase(Char self);

bool char_is_ascii_whitespace(Char self);


/// Including non-ASCII
/// Add support for unicode alphabets from other languages.

bool char_is_alphabetic(Char self);

bool char_is_alphanumeric(Char self);

bool char_is_control(Char self);

bool char_is_lowercase(Char self);

bool char_is_numeric(Char self);

bool char_is_uppercase(Char self);

bool char_is_whitespace(Char self);


size_t char_len_utf16(Char self);

size_t char_len_utf8(Char self);


Char char_to_ascii_lowercase(Char self);

Char char_to_ascii_uppercase(Char self);


Char char_from_u32(uint32_t i);


Char char_from_u32_unchecked(uint32_t i);


Char char_read(const void *src);

Char char_read_back(const void *src);

size_t char_write(Char self, void *destination);

void char_put(Char c, FILE *stream);


/**
```c
setlocale(LC_ALL, "");
wchar_t wc = getwchar();
printf("%u\n", wc);
```
With and without setlocale.
echo -n 'न' | ./main -> 2344
echo -n 'न' | ./main -> 4294967295 = 0xFFFFFFFF
echo -n 'न' | xxd -> 00000000: e0a4 a8

fgetwc is the wide-character version of fgetc;
it reads c as a multibyte character or a wide character
according to whether stream is opened in text mode or binary mode.

It should be able to read char from utf-8 stream.
*/
Char char_get(FILE *stream);


#endif /* STDC_CHAR_H */