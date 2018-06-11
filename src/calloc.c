#include "malloc.h"

void*	calloc(size_t count, size_t size)
{
	void* tmp;
	int	totSize;

	ft_printf("CALLOC(%lu, %lu)\n", count, size);
	totSize = count * size;

	if (!(tmp = malloc(totSize)))
		return NULL;
	ft_bzero(tmp, totSize);
	return tmp;
}