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

/**
 * @brief
 * @note		If tinyRoot == NULL:
 * 				init tinyRoot
 * 			findFreeSpace (saved in pgePointer.toReturn)
 * 			!if pgeP.toReturn: ( means not enough space free on the heap)
 * 				alloc new Page
 * 			if size > pgeP.toReturn->allocSize + 20:
 * 				tmp = splitMemory()
 *
 * @param  size:
 * @retval None
 */
void	handleTiny(size_t size)
{
	if (!pgePointers.rootTiny)
		if (!initRootTiny(size))
			return;
	findFreeBlock(pgePointers.rootTiny, size);
	if (!pgePointers.toReturn) // not enough place on the heap, need to allocate a new page.
	{
		getNewPage(createNewMemCtrl(pgePointers.lastTinyCtrl), size);
		if (pgePointers.errors)
			return;
		pgePointers.toReturn = pgePointers.lastTinyCtrl;
		// addNode(&pgePointers.rootTiny, pgePointers.toReturn);
	}
	else
	{
		removeNode(pgePointers.toReturn);
		checkHeight(pgePointers.rootTiny);
	}
	if (size + 24 <= pgePointers.toReturn->allocatedSize)
		addNode(&pgePointers.rootTiny, splitMemory(size));
}

int	initRootTiny(size_t size)
{
	pgePointers.memCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
	if (!(pgePointers.firstTinyCtrl = getNewPage(NULL, pgePointers.memCtrlSizeLeft)) ||
												!(getNewPage(pgePointers.firstTinyCtrl, size)))
		return 0;
	pgePointers.firstTinyCtrl->next = NULL;
	pgePointers.memCtrlSizeLeft -= MEM_CTRL_SIZE;
	pgePointers.lastTinyCtrl = pgePointers.firstTinyCtrl;
	pgePointers.rootTiny = pgePointers.firstTinyCtrl;

	return 1;
}