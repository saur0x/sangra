- `char c = 'न';`
    - `mov     BYTE PTR [rbp-5], -88`
    - `-88` = `(14722216 & 0xFF) - 128 - 128`
    - warning: multi-character character constant [-Wmultichar]
    - warning: overflow in implicit constant conversion [-Woverflow]
    - "%hhu %hhd" -> "168 -88"

- `char c = "न";`
    - `.string "\340\244\250"`
    - warning: initialization makes integer from pointer without a cast [-Wint-conversion]

- `wchar_t wc = L'न';`
    - `mov     DWORD PTR [rbp-4], 2344`
    - `ord('न')` = 2344

- `uint32_t c = 'न';`
    - `mov     DWORD PTR [rbp-8], 14722216`
    - `14722216` = `b'\x00\xe0\xa4\xa8'`
    - `'न'.encode()` = `b'\xe0\xa4\xa8'`

- `S.encode(encoding='utf-8', errors='strict') -> bytes`
- `bytes(string, encoding[, errors]) -> bytes`
- `getdefaultencoding() -> string`
    - Return the current default string encoding used by the Unicode implementation.
- String literals are stored in read-only memory (.rodata). If you try to write to one, you will crash most likely.


## Resources
- <https://www.joelonsoftware.com/2003/10/08/>
- <https://www.geeksforgeeks.org/wide-char-and-library-functions-in-c/>
- <https://en.wikipedia.org/wiki/Escape_sequences_in_C>