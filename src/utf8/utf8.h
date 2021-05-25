#ifndef STDC_UTF8_H
#define STDC_UTF8_H


#include <stdint.h>
#include <stddef.h>


// x is char for first and char * for others.
#define UTF8_IS_CONTINUATION(x) (((x) & 0xC0) == 0x80)
#define UTF8_IS_1(x) ((x[0] & 0x80) == 0x00)
#define UTF8_IS_2(x) ((x[0] & 0xE0) == 0xC0 && UTF8_IS_CONTINUATION(x[1]))
#define UTF8_IS_3(x) ((x[0] & 0xF0) == 0xE0 && UTF8_IS_CONTINUATION(x[1]) \
    && UTF8_IS_CONTINUATION(x[2]))
#define UTF8_IS_4(x) ((x[0] & 0xF8) == 0xF0 && UTF8_IS_CONTINUATION(x[1]) \
    && UTF8_IS_CONTINUATION(x[2]) && UTF8_IS_CONTINUATION(x[3]))


#define UTF8_GET_COUNT(code_point) ((code_point > 0x007F) + (code_point > 0x07FF) \
    + (code_point > 0xFFFF) + (code_point > 0x1FFFFF) + 1)


#define UTF8_GET_MASK(count) (0xF0E0C000 >> (8 * (count - 1)) & 0xFF)


#define UTF8_U8_TO_U32(PTR) (* (uint32_t *) PTR)
#define UTF8_U32_TO_U8(PTR) ((uint8_t *) PTR)


#define UTF8_IS_CODE_POINT(code_point) (0 <= code_point && code_point <= 0x1FFFFF)
#define UTF8_IS_SCALAR(code_point) \
    ((0 <= code_point && code_point <= 0xD7FF16) \
    || (0xE00016 <= code_point && code_point <= 0x10FFFF16))


/**
Returns the number of bytes by counting starting bits in first byte.
# Notes
Returns 0 if the byte is an invalid first byte.
*/
size_t utf8_byte_count(uint8_t byte);


uint32_t utf8_encode(uint32_t code_point);


uint32_t utf8_decode(uint32_t bytes);


uint8_t utf8_is_valid(uint32_t bytes);


/// Function implementation for macros with type checking.
/// These should be used instead of macros when using outside this file.

/**
0 to D7FF16 and E00016 to 10FFFF16 inclusive
*/
uint8_t utf8_is_scalar(uint32_t code_point);

uint8_t utf8_is_code_point(uint32_t code_point);

uint32_t utf8_u8_to_u32(uint8_t *ptr);


uint8_t *utf8_u32_to_u8(uint32_t *ptr);


uint8_t utf8_get_mask(uint8_t count);

uint8_t utf8_get_count(uint32_t code_point);


#endif /* STDC_UTF8_H */