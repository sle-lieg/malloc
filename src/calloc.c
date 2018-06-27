#include "malloc.h"

void*	calloc(size_t count, size_t size)
{
	// if (pges_ctrl.debug < 1 && pges_ctrl.debug < 1000)
	// ft_printf("CALLOC(%lu, %lu) = ", count, size);
	void*	tmp;

	size = (size <= SMALL_MAX ? align_memory16(size * count) : align_memory_page_size(size * count));
	// size = align_memory(size * count);
	// ft_printf("%lu\n", size);

	if (!(tmp = malloc(size)))
		return NULL;
	ft_bzero(tmp, size);
	return tmp;
}
