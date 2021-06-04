/**
gcc -o -Wall -o test test.c -I ../../src
echo -n 'न' | ./test
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "char.h"
#include "utf8.h"


int main(void)
{
    // char raw[4] = "😳"; Char code_point = 128563;
    // char raw[4] = "д"; Char code_point = 1076;
    char raw[4] = "न"; Char code_point = 2344;
    uint8_t *uraw = (uint8_t *) raw;

    #ifndef AUTOMATIC_TESTING
        Char c = char_get(stdin);
    #else
        Char c = char_read("न");
    #endif
    assert(c == utf8_decode(utf8_u8_to_u32(uraw)));

    char_put(c, stdout);

    Char read_raw = char_read(raw);
    assert(read_raw == code_point && read_raw == c);

    Char read_back_raw = char_read_back(raw + utf8_get_count(code_point) - 1);
    assert(read_back_raw == code_point);

    char new_raw[4] = { 0 };
    char_write(c, new_raw);
    assert(!strncmp(raw, new_raw, 4));

    return 0;
}