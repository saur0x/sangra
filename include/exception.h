#ifndef STDC_EXCEPTION_H
#define STDC_EXCEPTION_H


#include <stdlib.h>
#include <stdint.h>
#include <setjmp.h>


#define TRY																		\
	EXCEPTION_STACK = exception_stack_push(EXCEPTION_STACK);					\
	if (!(EXCEPTION.type = setjmp(EXCEPTION_STACK->state)))

/**
Catch and set the `Caught` flag
*/
#define CATCH(E) else if (EXCEPTION.type == E && exception_stack_flag_set(EXCEPTION_STACK, Caught))
#define CATCHALL else if (exception_stack_flag_set(EXCEPTION_STACK, Caught))

/**
Sets a jump at the front of stack so the program flow can return here
if the exception was never caught even at higher levels.
*/
#define THROW(E, ...) {															\
	EXCEPTION.type = E;															\
	ExceptionStack *front_stack = exception_stack_push_front(EXCEPTION_STACK);	\
	if (!EXCEPTION_STACK) EXCEPTION_STACK = front_stack;						\
	setjmp(front_stack->state);													\
	if (EXCEPTION_STACK->previous) {											\
		exception_stack_flag_set(EXCEPTION_STACK, Threw);						\
		longjmp(EXCEPTION_STACK->state, EXCEPTION.type);						\
	} else {																	\
		PANIC(#E ": " __VA_ARGS__);												\
	}																			\
}



/*
#define THROW(E, ...)															\
	EXCEPTION.type = E;															\
	setjmp(exception_stack_push_front(EXCEPTION_STACK)->state);					\
																				\
	if (EXCEPTION_STACK) {														\
		exception_stack_flag_set(EXCEPTION_STACK, Threw);						\
		longjmp(EXCEPTION_STACK->state, EXCEPTION.type);						\
	} else {																	\
		PANIC(#E ": " __VA_ARGS__);												\
	}
*/

/*
#define PROPAGATE																\
	printf("%lu", exception_stack_depth(EXCEPTION_STACK));						\
	EXCEPTION_STACK = exception_stack_pop(EXCEPTION_STACK);						\
	exception_stack_flag_set(EXCEPTION_STACK, Threw);							\
	longjmp(EXCEPTION_STACK->state, EXCEPTION.type)
*/

#define PROPAGATE {																\
	EXCEPTION_STACK = exception_stack_pop(EXCEPTION_STACK);						\
	if (EXCEPTION_STACK) {														\
		exception_stack_flag_set(EXCEPTION_STACK, Threw);						\
		longjmp(EXCEPTION_STACK->state, EXCEPTION.type);						\
	} else {																	\
		PANIC("...");															\
	}																			\
}

#define RESOLVE EXCEPTION_STACK = exception_stack_pop(EXCEPTION_STACK)


#define ELSE if (!exception_stack_flag_get(EXCEPTION_STACK, Threw))

/**
Pop off the exception node from front if exception was raised and then caught.
*/
#define FINALLY {																\
	if (exception_stack_flag_get(EXCEPTION_STACK, Threw)						\
		&& exception_stack_flag_get(EXCEPTION_STACK, Caught))					\
	{ EXCEPTION_STACK = exception_stack_pop_front(EXCEPTION_STACK); RESOLVE; }	\
	else if (exception_stack_flag_get(EXCEPTION_STACK, Threw)					\
		&& !exception_stack_flag_get(EXCEPTION_STACK, Caught))					\
	{ PROPAGATE; }																\
	else { RESOLVE; }															\
}

#define PANIC(...) {															\
	fputs("thread 'main' panicked at '", stderr);								\
	fprintf(stderr, __VA_ARGS__);												\
	fprintf(stderr, "', %s:%d\n", __FILE__, __LINE__);							\
	exit(-1);																	\
}


enum ExceptionType
{
	NoException,
	IndexError = 0x01,
	ValueError,
};

enum
{
	Caught = 0b00000001,
	Threw = 0b00000010,
};


struct exception
{
	int type;

	/// TODO: Use stdc String instead of char * for error message.
	// String message;

	char *message;
};

typedef struct exception Exception;


struct exception_stack
{
	struct exception_stack *previous;
	jmp_buf state;
	uint8_t flags;
};

typedef struct exception_stack ExceptionStack;


struct exception_stack *exception_stack_push(struct exception_stack *previous);
struct exception_stack *exception_stack_pop(struct exception_stack *self);

struct exception_stack *exception_stack_push_front(struct exception_stack *self);
struct exception_stack *exception_stack_pop_front(struct exception_stack *self);

void exception_stack_free(struct exception_stack *self);

size_t exception_stack_depth(struct exception_stack *self);

uint8_t exception_stack_flag_get(struct exception_stack *self, uint8_t flag);
uint8_t exception_stack_flag_set(struct exception_stack *self, uint8_t flag);


#endif /* STDC_EXCEPTION_H */