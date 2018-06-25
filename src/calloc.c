#include "malloc.h"

void*	calloc(size_t count, size_t size)
{
	if (pges_ctrl.debug > 0)
		ft_printf("CALLOC(%lu, %lu) = ", count, size);
	void*	tmp;
	

	size = align_memory(size * count);
	// ft_printf("%lu\n", size);

	if (!(tmp = malloc(size)))
		return NULL;
	ft_bzero(tmp, size);
	return tmp;
}
