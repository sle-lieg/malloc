#include "malloc.h"

void*	calloc(size_t count, size_t size)
{
	void* tmp;

	ft_printf("Calloc(%lu, %lu)\n", count, size);
	if (!(tmp = malloc(count * size)))
		return NULL;
	ft_bzero(tmp, count * size);
	return tmp;
}