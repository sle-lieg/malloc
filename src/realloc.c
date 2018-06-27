#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
	// if (pges_ctrl.debug < 1 && pges_ctrl.debug < 1000)
	if (pges_ctrl.debug < 1 && pges_ctrl.debug < 1000)
		ft_printf("REALLOC(%p, %lu)", ptr, size);
	t_mem_ctrl* to_realloc;

	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (malloc(0));
	}
	assert(pges_ctrl.root != NULL);
	to_realloc = find_mem_ctrl(pges_ctrl.root, ptr);
	// assert(to_realloc != NULL);
	if (to_realloc)
	{
		if (to_realloc->size >= size)
			return (to_realloc->addr);
		if (!(malloc(size)))
			return (NULL);
		ft_memmove(pges_ctrl.ret->addr, ptr, to_realloc->size);
		free(ptr);
		return (pges_ctrl.ret->addr);
	}
	// else
	// {
	// 	ft_printf(" BAD ADDRESS[%p] %d | ", ptr, pges_ctrl.debug);
	// }
	if (pges_ctrl.debug < 1 && pges_ctrl.debug < 1000)
	{
		show_alloc_mem();
		printTree2(pges_ctrl.root);
	// 	print_empty();
	}
	// return (malloc(size));
	// return (ptr);
	return (NULL);
}
