#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <wchar.h>
#include <locale.h>


#include "utf8/utf8.h"


int main(void)
{
    // char raw[4] = "त";
    char raw[4] = "\xc3\xbf";
    uint32_t decoded = utf8_decode(utf8_u8_to_u32(raw));
    uint32_t encoded = utf8_encode(decoded);
    char *raw_again = utf8_u32_to_u8(&encoded);

    assert(utf8_is_valid(encoded));
    assert(!strncmp(raw, raw_again, 4));

    printf("%.4s\t%.4s\n", raw, raw_again);
    printf("%.4s\n", (char *) &encoded);
}
/*
int main(void)
{
    // setlocale(LC_ALL, "");

    // wchar_t wc = fgetwc(stdin);
    // printf("%u\n", wc);

    // char *s = "नमस्ते";
    char *c = "न";
    // char *c = "A";
    printf("%u\n", utf8_is_3(c));

    // char *s = "\340\244\250\340\244\256\340\244\270\340\245\215\340\244\244\340\245\207";
    // char *c = "\340\244\250";

    // char *s = "\xe0\xa4\xa8\xe0\xa4\xae\xe0\xa4\xb8\xe0\xa5\x8d\xe0\xa4\xa4\xe0\xa5\x87";
    // char *c = "\xe0\xa4\xa8";

    // puts(s);
    // printf("%.*s\n", 2, c);

    // size_t length = strlen(c);

    // for (size_t i = 0; i < length; ++i)
    //     printf("%hhu\n", c[i]);

    // printf("%lu\n", length);


    // wchar_t wc = L'न';

    // printf("%lu\t%lu\n", sizeof(wchar_t), sizeof(wint_t));

    // wprintf(L"%ls\n", wc);

    return 0;
}
*/