#include "char.h"


/// Rust functionality
/// TODO: Encoding, decoding from utf8 and utf16 and escape functions.

Char char_from_digit(uint32_t num, uint32_t radix)
{
    if (radix > 36) {
        // EXCEPTION: radix too large
        return 0;
    }

    if (num >= radix) {
        // EXCEPTION: num is not a single digit
        return 0;
    }

    return num <= 9 ? num + '0' : num + 'a' - 10;
}

bool char_is_digit(Char self, uint32_t radix)
{
    return char_to_digit(self, radix) != 0xFF;
}

uint32_t char_to_digit(Char self, uint32_t radix)
{
    if (radix > 36) {
        // EXCEPTION: radix too large
        return 0xFF;
    }

    uint8_t num = 0xFF;

    if ('0' <= self && self <= '9')
        num = self - '0';
    else if ('A' <= self && self <= 'Z')
        num = self - 'A' + 10;
    else if ('a' <= self && self <= 'z')
        num = self - 'a' + 10;

    if (num >= radix) {
        // EXCEPTION: num is not a single digit
        return 0xFF;
    }

    return num;
}


/// ASCII functions

bool char_eq_ignore_ascii_case(Char self, Char other)
{
    return char_to_ascii_lowercase(self) == char_to_ascii_lowercase(other);
}

bool char_is_ascii(Char self)
{
    return 0 <= self && self <= 0x7F;
}

bool char_is_ascii_alphabetic(Char self)
{
    return ('A' <= self && self <= 'Z') || ('a' <= self && self <= 'z');
}

bool char_is_ascii_alphanumeric(Char self)
{
    return char_is_ascii_digit(self) || char_is_ascii_alphabetic(self);
}

bool char_is_ascii_control(Char self)
{
    return (0x0000 <= self && self <= 0x001F) || self == 0x007F;
}

bool char_is_ascii_digit(Char self)
{
    return '0' <= self && self <= '9';
}

bool char_is_ascii_graphic(Char self)
{
    return '!' <= self && self <= '~';
}

bool char_is_ascii_hexdigit(Char self)
{
    return ('0' <= self && self <= '9') || ('A' <= self && self <= 'F') || ('a' <= self && self <= 'f');
}

bool char_is_ascii_lowercase(Char self)
{
    return 'a' <= self && self <= 'z';
}

bool char_is_ascii_punctuation(Char self)
{
    return ('!' <= self && self <= '/') || (':' <= self && self <= '@') || ('[' <= self && self <= '`') || ('{' <= self && self <= '~');
}

bool char_is_ascii_uppercase(Char self)
{
    return 'A' <= self && self <= 'Z';
}

bool char_is_ascii_whitespace(Char self)
{
    return self == 0x20
        || self == 0x09
        || self == 0x0A
        // || self == 0x0B
        || self == 0x0C
        || self == 0x0D;
}


/// Including non-ASCII
/// Add support for unicode alphabets from other languages.

bool char_is_alphabetic(Char self)
{
    return ('A' <= self && self <= 'Z') || ('a' <= self && self <= 'z');
}

bool char_is_alphanumeric(Char self)
{
    return char_is_alphabetic(self) || char_is_numeric(self);
}

bool char_is_control(Char self)
{
    return char_is_ascii_control(self);
}

bool char_is_lowercase(Char self)
{
    return char_is_ascii_lowercase(self);
}

bool char_is_numeric(Char self)
{
    return char_is_ascii_digit(self);
}

bool char_is_uppercase(Char self)
{
    return char_is_uppercase(self);
}

bool char_is_whitespace(Char self)
{
    return char_is_ascii_whitespace(self)
        || (0x0009 <= self && self <= 0x000D)
        || self == 0x0020
        || self == 0x0085
        || self == 0x00A0
        || self == 0x1680
        || (0x2000 <= self && self <= 0x200A)
        || self == 0x2028
        || self == 0x2029
        || self == 0x202F
        || self == 0x205F
        || self == 0x3000;
}


size_t char_len_utf16(Char self)
{
    // Unimplemented
    return 0;
}

size_t char_len_utf8(Char self)
{
    return utf8_get_count(self);
}


Char char_to_ascii_lowercase(Char self)
{
    if ('A' <= self && self <= 'Z')
        return self + 32;
    return self;
}

Char char_to_ascii_uppercase(Char self)
{
    if ('a' <= self && self <= 'z')
        return self - 32;
    return self;
}


Char char_from_u32(uint32_t i)
{
    if (!utf8_is_scalar(i)) {
        // EXCEPTION: Not a utf-8 scalar value
        return 0;
    }

    return i;
}


Char char_from_u32_unchecked(uint32_t i)
{
    return i;
}


/**
Return number of bytes to skip to get to next char.
*/
size_t char_skip(const void *src)
{
    uint8_t *source = (uint8_t *) src;

    size_t count = 0;

    for (;
        count < 4
        && UTF8_IS_CONTINUATION(*source);
        ++count, ++source
    );

    return count;
}

Char char_read(const void *src)
{
    uint8_t *source = (uint8_t *) src;

    uint8_t byte_array[4] = { 0 };

    byte_array[0] = source[0];

    size_t count = utf8_byte_count(byte_array[0]);
    if (!count) {
        // ERROR
        return -1;
    }

    // Early access to ASCII characters.
    if (byte_array[0] <= 0x7F)
        return byte_array[0];
    
    for (size_t i = 1; i < count; ++i)
        byte_array[i] = source[i];

    uint32_t bytes = utf8_u8_to_u32(byte_array);

    if (!utf8_is_valid(bytes)) {
        // EXCEPTION
        return -1;
    }

    return utf8_decode(bytes);
}

Char char_read_back(const void *src)
{
    uint8_t *source = (uint8_t *) src;

    size_t count = 1;

    for (;
        count <= 4
        && UTF8_IS_CONTINUATION(*source);
        ++count, --source
    );

    // assert(utf8_byte_count(*source) == count);

    return char_read(source);
}

size_t char_write(Char self, void *destination)
{
    size_t count = utf8_get_count(self);
    uint32_t bytes = utf8_encode(self);
    uint8_t *byte_array = utf8_u32_to_u8(&bytes);
    memcpy(destination, byte_array, count);
    return count;
}

void char_put(Char c, FILE *stream)
{
    uint32_t bytes = utf8_encode(c);
    uint8_t *byte_array = utf8_u32_to_u8(&bytes);
    fwrite(byte_array, 4, 1, stream);
}

Char char_get(FILE *stream)
{
    uint8_t byte_array[4] = { 0 };

    fread(byte_array, 1, 1, stream);

    // Early access to ASCII characters.
    if (byte_array[0] <= 0x7F)
        return (Char) byte_array[0];

    // UTF-8
    size_t count = utf8_byte_count(byte_array[0]);

    if (!count) {
        fseek(stream, -1, SEEK_CUR);
        // ERROR
        return 0;
    }

    fread(byte_array + 1, 1, count - 1, stream);

    uint32_t bytes = utf8_u8_to_u32(byte_array);

    if (!utf8_is_valid(bytes)) {
        fseek(stream, -count, SEEK_CUR);
        // EXCEPTION
        return 0;
    }

    return utf8_decode(bytes);
}