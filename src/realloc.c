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

		return checkSize(size);
		// if (pgePointers.errors)
		// 	return NULL;
		// return (pgePointers.toReturn->pageAddr);
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

void*	checkSize(size_t size)
{
	void*			tmp;
	t_mem_ctrl* toFree;

	toFree = pgePointers.toReturn;
	if (size <= toFree->allocatedSize)
	{
		toFree->requiredSize = size;
		return toFree->pageAddr;
	}
	if (!(tmp = malloc(size)))
		return NULL;
	ft_memmove(tmp, toFree->pageAddr,
		toFree->requiredSize);
	free(toFree->pageAddr);
	return tmp;
	// pgePointers.toReturn = tmp;
}