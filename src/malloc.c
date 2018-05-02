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

void	handleTiny(size_t size)
{
	if (!pgePointers.rootTiny)
	{
		pgePointers.memCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
		if (!(pgePointers.firstTinyCtrl = getNewPage(NULL, pgePointers.memCtrlSizeLeft)) ||
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
	splitMemory(size);
}