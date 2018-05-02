#include "malloc.h"

void*	ft_malloc(size_t size)
{
	pgePointers.toReturn = NULL;
	pgePointers.pageSize = getpagesize();
	pgePointers.size = size;
	size = (size % MEM_ALIGN) ?
		((size >> MEM_ALIGN_SHIFT) << MEM_ALIGN_SHIFT) + MEM_ALIGN : size;
	if (size <= TINY_MAX)
		handleTiny(size);
	// else if (size < SMALL_MAX)
	// 	handleSmall(size);
	// else
	// 	handleLarge(size);
	if (pgePointers.errors)
		return NULL;
	return pgePointers.toReturn->pageAddr;
}

// void	handleTiny(size_t size)
// {
// 	if (!pgePointers.rootTiny)
// 	{
// 		pgePointers.memCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
// 		if (!(pgePointers.firstTinyCtrl =
// 			getNewPage(NULL, pgePointers.memCtrlSizeLeft)) ||
// 			!(getNewPage(pgePointers.firstTinyCtrl, size)))
// 			return;
// 		pgePointers.memCtrlSizeLeft -= MEM_CTRL_SIZE;
// 		pgePointers.lastTinyCtrl = pgePointers.firstTinyCtrl;
// 		pgePointers.rootTiny = pgePointers.firstTinyCtrl;
// 	}
// 	findFreeBlock(pgePointers.rootTiny, size);
// 	if (!pgePointers.toReturn) // not enough place on the heap, need to allocate a new page.
// 	{
// 		if (!(getNewPage(createNewMemCtrl(pgePointers.lastTinyCtrl), size)))
// 	}
// }

void	handleTiny(size_t size)
{
	if (!pgePointers.rootTiny)
	{
		pgePointers.memCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
		if (!(pgePointers.firstTinyCtrl =
			getNewPage(NULL, pgePointers.memCtrlSizeLeft)) ||
			!(getNewPage(pgePointers.firstTinyCtrl, size)))
			return;
		pgePointers.memCtrlSizeLeft -= MEM_CTRL_SIZE;
		pgePointers.lastTinyCtrl = pgePointers.firstTinyCtrl;
		pgePointers.rootTiny = pgePointers.firstTinyCtrl;
	}
	findFreeBlock(pgePointers.rootTiny, size);
	if (!pgePointers.toReturn) // not enough place on the heap, need to allocate a new page.
	{
		getNewPage(createNewMemCtrl(pgePointers.lastTinyCtrl), size));
		if (pgePointers.errors)
			return;
		pgePointers.toReturn = pgePointers.lastTinyCtrl;
	}

	/**
	 * split le block a return, faire les links, et ajouter les block crees dans
	 * l' arbre de tri par taille.
	 */
	splitMemCtrl(size);
}

t_mem_ctrl*	createNewMemCtrl(t_mem_ctrl* memCtrlSplited)
{
	t_mem_ctrl* newMemCtrl;

	if (pgePointers.memCtrlSizeLeft < MEM_CTRL_SIZE)
	{
		pgePointers.memCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
		if(!(pgePointers.lastTinyCtrl->next = getNewPage(NULL, pgePointers.memCtrlSizeLeft))
			return NULL;
		newMemCtrl = pgePointers.lastTinyCtrl->next;
		// if (!newMemCtrl->next = getNewPage(NULL, )
	}
	else
		newMemCtrl = pgePointers.lastTinyCtrl + MEM_CTRL_SIZE;
	newMemCtrl->prev = memCtrlSplited;
	memCtrlSplited->next = newMemCtrl;
	pgePointers.lastTinyCtrl = newMemCtrl;
	pgePointers.memCtrlSizeLeft -= MEM_CTRL_SIZE;

	return newMemCtrl;
}

// void	initTinyMapping(size_t size)
// {
// 	if (!(pgePointers.rootTiny = getNewPage(NULL, size)) ||
// 		!(pgePointers.tinyPage = getNewPage(NULL, size)))
// 		return;
// 	pgePointers.rootTiny->pageAddr = pgePointers.tinyPage;
// 	pgePointers.rootTiny->allocatedSize = pgePointers.pageSize;
// 	pgePointers.rootTiny->free = 1;
// }

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