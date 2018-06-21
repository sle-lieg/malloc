#include "malloc.h"

void *reallocf(void *ptr, size_t size)
{
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
	if ((pges_ctrl.ret = malloc(size)))
		ft_memmove(pges_ctrl.ret->addr, ptr, to_realloc->size);
	free(ptr);
	return (pges_ctrl.ret ? pges_ctrl.ret->addr : NULL);
}
