#include "malloc.h"

#include <string.h>

void *reallocf(void *ptr, size_t size)
{
	// ft_printf("REALLOC F (%p, %lu)", ptr, size);
	void* tmp;

	if (!(tmp = realloc(ptr, size)))
		free(ptr);
	return tmp;
}