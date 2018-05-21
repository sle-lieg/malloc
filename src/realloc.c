#include "malloc.h"

#include <string.h>

void *realloc(void *ptr, size_t size)
{
	ft_printf("REALLOC(%p, %lu)", ptr, size);
	// ft_printf("Realloc(%p, %lu)", ptr, size);
	if (!ptr)
		return (malloc(size));
	else
	{
		if (!checkLimit(size) || !(pgePointers.toReturn = getMemCtrl(ptr)))
			return NULL;

		// ft_printf("(old = %lu)\n", pgePointers.toReturn->allocatedSize);

		checkSize(size);
		if (pgePointers.errors)
			return NULL;
		return (pgePointers.toReturn->pageAddr);		
	}
}
// TODO: multi threads
t_mem_ctrl* getMemCtrl(void* ptr)
{
	t_mem_ctrl* tmp;

	tmp = pgePointers.firstTinyCtrl;
	while (tmp)
	{
		if (tmp->pageAddr == ptr)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void	checkSize(size_t size)
{
	void* tmp;

	if (size <= pgePointers.toReturn->allocatedSize)
	{
		pgePointers.toReturn->requiredSize = size;
		return;
	}
	if (!(tmp = malloc(size)))
	{
		pgePointers.errors |= MMAP_BAD_ALLOC;
		return;
	}
	ft_memmove(tmp, pgePointers.toReturn->pageAddr,
		pgePointers.toReturn->requiredSize);
	free(pgePointers.toReturn->pageAddr);
	pgePointers.toReturn = tmp;
}