```c
#define CONCATENATE(X, Y) X ## _ ## Y
#define array_NAME CONCATENATE(array, NAME)

void array_copy(array_t *self, array_t *other)
{
	if (other == NULL)
		other = (array_t *) malloc(sizeof(array_t));
}

#undef CONCATENATE
#undef METHOD
```