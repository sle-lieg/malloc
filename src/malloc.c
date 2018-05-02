#include "malloc.h"

void*	ft_malloc(size_t size)
{
	pgePointers.toReturn = NULL;
	pgePointers.pageSize = getpagesize();
	pgePointers.size = size;
	size = (size % MEM_ALIGN) ? ((size >> MEM_ALIGN_SHIFT) << MEM_ALIGN_SHIFT) + MEM_ALIGN : size;
	if (size <= TINY_MAX)
		handleTiny(size);
	// else if (size < SMALL_MAX)
	// 	handleSmall(size);
	// else
	// 	handleLarge(size);
	if (pgePointers.errors)
		return NULL;
	return pgePointers.toReturn;
}

void	handleTiny(size_t size)
{
	t_mem_ctrl* tmp;

	if (!pgePointers.rootTiny)
	{
		if (!(pgePointers.rootTiny = getNewPage(NULL, size)) ||
			!(pgePointers.tinyPage = getNewPage(NULL, size)))
			return;
		pgePointers.rootTiny->pageAddr = pgePointers.tinyPage;
		pgePointers.rootTiny->allocatedSize = pgePointers.pageSize;
		pgePointers.rootTiny->free = 1;
		// createMemCtrl(pgePointers.rootTiny, pgePointers.tinyPage, size);
	}
	findFreeBlock(pgePointers.rootTiny, size);
}

// void	handleSmall(size_t size)
// {
// 	if (!pgePointers.firstS)
// 		if (!(pgePointers.firstS = getNewPage(NULL, size)))
// 			return;
// 	findFreeBlock(pgePointers.firstS, size);
// }

// void	handleLarge(size_t size)
// {
// 	if (!pgePointers.firstL)
// 		if (!(pgePointers.firstL = getNewPage(NULL, size)))
// 			return;
// 	findFreeBlock(pgePointers.firstL, size);
// }

void	show_alloc_mem()
{
	t_mem_ctrl* tmp;

	tmp = pgePointers.firstT;
	if (tmp)
		ft_printf("TINY : %p\n", tmp);	
	while (tmp)
	{
		ft_printf("%#5X - %#5X : %d octets\n", tmp->pageAddr, tmp->pageAddr + tmp->requiredSize, tmp->requiredSize);
		tmp = tmp->next;
	}
}