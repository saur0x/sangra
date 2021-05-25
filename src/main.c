// #include "vector/vector.h"
#define METHOD(NAME) CONCATENATE(STRUCT, NAME)
#define CONCATENATE(X, Y) X ## _ ## Y
#define STRUCT struct array


int main(void)
{
	// vector_t *vector = vector_new(NULL, sizeof(int));
METHOD(set)(x, y, z);
	return 0;
}
