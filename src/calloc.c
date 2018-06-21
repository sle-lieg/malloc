#include "malloc.h"

void*	calloc(size_t count, size_t size)
{
	void*	tmp;

	size = align_memory(count * size);

	if (!(tmp = malloc(size)))
		return NULL;
	ft_bzero(tmp, size);
	return tmp;
}
