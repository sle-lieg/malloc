#include "malloc.h"

void *reallocf(void *ptr, size_t size)
{
	t_mem_ctrl	*to_realloc;
	// char			*to_return;

	// to_return = NULL;
	// if (pges_ctrl.debug > 0)
	// 	ft_printf("REALLOC_F(%p, %lu)", ptr, size);
	to_realloc = NULL;
	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (malloc(16));
	}
	to_realloc = find_mem_ctrl(pges_ctrl.root, ptr);
	assert(to_realloc != NULL);
	// if ((to_return = malloc(size)))
	// ft_printf("REALLOCF (%p, %lu)\n", ptr, size);
	// assert(to_realloc != NULL);
	if (to_realloc)
	{
		if (to_realloc->size >= size)
			return (to_realloc->addr);
		if ((malloc(size)))
			ft_memmove(pges_ctrl.ret->addr, ptr, to_realloc->size);
		free(ptr);
		return (pges_ctrl.ret->addr);
	}
	return (malloc(size));
	// 	ft_memmove(to_return, ptr, to_realloc->size);
	// free(ptr);
	// return (to_return);
}
