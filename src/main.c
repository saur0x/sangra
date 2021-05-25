#include <stdio.h>

#include "char/char.h"
#include "string/chars.h"
#include "string/string.h"


int main(void)
{
	String *string = string_from_str(NULL, "Hello, World!");

	string_push(string, '\n');

	Char flushed = char_read("😳");
	string_push(string, flushed);

	string_push_str(string, "😉");

	puts(string_as_str(string));

	// Char iterator
	Chars *chars = chars_new(NULL, string);
	Char iter_char;

	while ((iter_char = chars_next(chars)) != CHAR_NULL) {
		char_put(iter_char, stdout);
	}

	free(chars);
	string_free(string);
	free(string);

	return 0;
}
