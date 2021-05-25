/**
gcc -o -Wall -o test test.c
./test
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>


#include "utf8.h"


int main(void)
{
    char raw[4] = "😳";
    uint32_t decoded = utf8_decode(utf8_u8_to_u32(raw));
    uint32_t encoded = utf8_encode(decoded);
    char *raw_again = utf8_u32_to_u8(&encoded);

    assert(utf8_is_valid(encoded));
    assert(!strncmp(raw, raw_again, 4));

    printf("%.4s\n", raw);
    printf("%.4s\n", raw_again);
    printf("%.4s\n", (char *) &encoded);
}