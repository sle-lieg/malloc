#include "malloc.h"

#include <string.h>

void *realloc(void *ptr, size_t size)
{
 	// if (!pges_ctrl.count)
		ft_printf("REALLOC(%p, %lu)", ptr, size);
	if (!ptr)
		return (malloc(size));
	else
	{
		if (!(pges_ctrl.toReturn = getMemCtrl(ptr)))
		// if (!checkLimit(size) || !(pges_ctrl.toReturn = getMemCtrl(ptr)))
			return NULL;
	}
	return checkSize(size);
}

// TODO: multi threads
t_mem_ctrl* getMemCtrl(void* ptr)
{
	t_mem_ctrl* tmp;

	tmp = pges_ctrl.fst_tiny;
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

	toFree = pges_ctrl.toReturn;
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
}
