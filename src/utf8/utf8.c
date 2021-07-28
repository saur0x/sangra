#include "utf8.h"


size_t utf8_byte_count(uint8_t byte)
{
    size_t count = 0;
    uint8_t mask = 0x80;

    for (; byte & mask && count < 8; ++count, mask >>= 1);

    return count ? (count <= 4) * count : 1;
}


uint32_t utf8_encode(uint32_t code_point)
{
    if (!UTF8_IS_CODE_POINT(code_point)) {
        // EXCEPTION: Invalid code_point
        return 0;
    }

    uint8_t byte_array[4] = { 0 };

    // Early access to ASCII characters.
    if (code_point <= 0x7F) {
        byte_array[0] = code_point;
        return UTF8_U8_TO_U32(byte_array);
    }

    uint8_t count = UTF8_GET_COUNT(code_point);
    uint8_t index = count;

    while (--index) {
        byte_array[index] = 0x80 | (code_point & 0x3F);
        code_point >>= 6;
    }

    byte_array[0] = UTF8_GET_MASK(count) | (code_point & 0x7F);

    return UTF8_U8_TO_U32(byte_array);
}


uint32_t utf8_decode(uint32_t bytes)
{
    uint8_t *byte_array = (uint8_t *) &bytes;

    // Early access to ASCII characters.
    if (byte_array[0] <= 0x7F)
        return byte_array[0];

    uint8_t count = utf8_byte_count(byte_array[0]);

    if (!count) {
        // EXCEPTION: Invalid bytes
        return 0;
    }

    uint32_t code_point = byte_array[0] & ~UTF8_GET_MASK(count);

    for (size_t i = 1; i < count; ++i) {

        if (!UTF8_IS_CONTINUATION(byte_array[i])) {
            // EXCEPTION: Invalid continuation byte
            return 0;
        }

        code_point <<= 6;
        code_point |= byte_array[i] & 0x3F;
    }

    return code_point;
}


uint8_t utf8_is_valid(uint32_t bytes)
{
    uint8_t *byte_array = (uint8_t *) &bytes;

    uint8_t count = utf8_byte_count(byte_array[0]);

    if (!count)
        return 0;

    for (size_t i = 1; i < count; ++i) {
        if (!UTF8_IS_CONTINUATION(byte_array[i]))
            return 0;
    }

    return 1;
}


/// Function implementation for macros with type checking.
/// These functions should be used instead of macros when using outside this library.


uint8_t utf8_is_scalar(uint32_t code_point)
{
    // 0 to D7FF16 and E00016 to 10FFFF16 inclusive
    return UTF8_IS_SCALAR(code_point);
}

uint8_t utf8_is_code_point(uint32_t code_point)
{
    return UTF8_IS_CODE_POINT(code_point);
}


uint32_t utf8_u8_to_u32(uint8_t *ptr)
{
    return UTF8_U8_TO_U32(ptr);
}


uint8_t *utf8_u32_to_u8(uint32_t *ptr)
{
    return UTF8_U32_TO_U8(ptr);
}


uint8_t utf8_get_mask(uint8_t count)
{
    return UTF8_GET_MASK(count);
}

uint8_t utf8_get_count(uint32_t code_point)
{
    return UTF8_GET_COUNT(code_point);
}