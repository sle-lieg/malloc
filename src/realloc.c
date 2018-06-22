#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
	if (pges_ctrl.debug)
		ft_printf("REALLOC(%p, %lu)", ptr, size);
	t_mem_ctrl* to_realloc;

	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (malloc(0));
	}
	to_realloc = find_mem_ctrl(pges_ctrl.root, ptr);
	assert(to_realloc != NULL);
	if (to_realloc->size >= size)
		return (to_realloc->addr);
	if (!(malloc(size)))
		return (NULL);
	ft_memmove(pges_ctrl.ret->addr, ptr, to_realloc->size);
	free(ptr);
	return (pges_ctrl.ret->addr);
}
