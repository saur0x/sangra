// gcc -I ../../include -o test test.c exception.c

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "exception.h"


Exception exception = { NoException, NULL };
#define EXCEPTION exception

ExceptionStack *stack = NULL;
#define EXCEPTION_STACK stack


void may_throw()
{
	puts("[*] Entry");

	if (rand() % 100 < 50) {
		puts("[*] Throwing");
		THROW(IndexError);
	}

	puts("[*] Skipped");
}


int main(void)
{
	srand(time(NULL));

	if (rand() % 100 < 25)
		THROW(IndexError, "Oops! %d", 25);

	TRY {
		THROW(IndexError, "Oh no %d", 25);
	}
	CATCH(IndexError) {}
	FINALLY {}

	TRY {
		puts("[+] Entry");

		TRY {
			puts("[-] Entry");
			// THROW(IndexError);

			may_throw();
		}
		CATCH(ValueError) {
			puts("[-] Caught");
		}
		ELSE {
			puts("[-] Else: Didn't Throw");
		}
		FINALLY {
			puts("[-] Finally: Didn't Throw or Caught");
		}
	}
	CATCH(IndexError) {
		PANIC("IndexError: %d", 100);
	}
	// CATCH(ValueError) {
	// 	PANIC("ValueError: %d", 101);
	// }
	// CATCHALL {
	// 	puts("[+] Other");
	// }
	ELSE {
		puts("[+] Else: Didn't Throw");
	}
	FINALLY {
		puts("[+] Finally: Didn't Throw or Caught");
	}

	// All exception stack nodes are automatically freed
	// exception_stack_free(stack);
	assert(EXCEPTION_STACK == NULL);

	return 0;
}