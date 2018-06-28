#include "malloc.h"

void*	calloc(size_t count, size_t size)
{
	void*	tmp;

	size = (size <= SMALL_MAX ? align_memory16(size * count) : align_memory_page_size(size * count));
	if (!(tmp = malloc(size)))
		return NULL;
	ft_bzero(tmp, size);
	return tmp;
}
