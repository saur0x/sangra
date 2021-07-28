`char` is always four bytes in size. This is a different representation than a given character would have as part of a String.
Another implication of the 4-byte fixed size of a char is that per-char processing can end up using a lot more memory.

#### Code Point
Any value in the Unicode codespace; that is, the range of integers from 0 to 10FFFF16. Not all code points are assigned to encoded characters. A value, or position, for a character, in any coded character set.

#### Unicode Scalar Value
Any Unicode code point except high-surrogate and low-surrogate code points. In other words, the ranges of integers 0 to D7FF16 and E00016 to 10FFFF16 inclusive.

#### Code Point Type
Any of the seven fundamental classes of code points in the standard: Graphic, Format, Control, Private-Use, Surrogate, Noncharacter, Reserved.

## Resources
- <https://en.wikipedia.org/wiki/Typedef>
- <https://doc.rust-lang.org/std/primitive.char.html>
- <http://www.unicode.org/glossary/#unicode_scalar_value>