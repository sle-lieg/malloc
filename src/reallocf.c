#include "malloc.h"

#include <string.h>

void *reallocf(void *ptr, size_t size)
{
	// ft_printf("REALLOC F (%p, %lu)", ptr, size);
	void* tmp;

	if (!(tmp = realloc(ptr, size)))
		free(ptr);
	return tmp;
}

// void *reallocf(void *ptr, size_t size)
// {
// 	ft_printf("Realloc F (%p, %lu)", ptr, size);
	
// 	if (!ptr)
// 		return (malloc(size));
// 	else
// 	{
// 		if (!(pgePointers.toReturn = getMemCtrl(ptr)))
// 			return NULL;
// 		if (!checkLimit(size))
// 		{
// 			free(pgePointers.toReturn->pageAddr);
// 			return NULL;
// 		}
// 		checkSizeF(size);
// 		if (pgePointers.errors)
// 			return NULL;
// 		return (pgePointers.toReturn->pageAddr);		
// 	}
// }
// // TODO: multi threads
// t_mem_ctrl* getMemCtrl(void* ptr)
// {
// 	t_mem_ctrl* tmp;

// 	tmp = pgePointers.firstTinyCtrl;
// 	while (tmp)
// 	{
// 		if (tmp->pageAddr == ptr)
// 			return tmp;
// 		tmp = tmp->next;
// 	}
// 	return NULL;
// }

// void	checkSizeF(size_t size)
// {
// 	void* tmp;

// 	if (size <= pgePointers.toReturn->allocatedSize)
// 	{
// 		pgePointers.toReturn->requiredSize = size;
// 		return;
// 	}
// 	if (!(tmp = malloc(size)))
// 	{
// 		pgePointers.errors |= MMAP_BAD_ALLOC;
// 		free(pgePointers.toReturn->pageAddr);
// 		return;
// 	}
// 	ft_memmove(tmp, pgePointers.toReturn->pageAddr,
// 		pgePointers.toReturn->requiredSize);
// 	free(pgePointers.toReturn->pageAddr);
// 	pgePointers.toReturn = tmp;
// }