#include "malloc.h"

void*	malloc(size_t size)
{
	ft_printf("MALLOC(%lu)\n", size);
	// ft_printf("Malloc(%lu): MEM_CTRL_SIZE=%lu\n", size, pgePointers.memCtrlSizeLeft);
	if (!checkLimit(size))
		return NULL;
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
	printAll();
	printTree2(pgePointers.rootTiny);
	// show_alloc_mem();
	return pgePointers.toReturn->pageAddr;
}

// TODO: remove or clean it
t_mem_ctrl*	getLastTinyLink()
{
	t_mem_ctrl* tmp;

	tmp = pgePointers.firstTinyCtrl;
	while (tmp->next)
		tmp = tmp->next;
	return tmp;
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
	if (!pgePointers.firstTinyCtrl)
		if (!initRootTiny(size))
			return;
	findFreeBlock(pgePointers.rootTiny, size);
	
	if (!pgePointers.toReturn) // not enough place on the heap, need to allocate a new page.
	{
		// ft_printf("RESISING");
		// if (!(pgePointers.toReturn = createNewMemCtrl(pgePointers.lastTinyCtrl)))
		if (!(pgePointers.toReturn = createNewMemCtrl(getLastTinyLink())))
		{
			// ft_printf("ERROR CREATE NMCTRL\n");
			return;
		}
		pgePointers.toReturn->free = FALSE;
		getNewPage(pgePointers.toReturn, size);
		if (pgePointers.errors)
			return;
		// pgePointers.toReturn = pgePointers.lastTinyCtrl;
		// addNode(&pgePointers.rootTiny, pgePointers.toReturn);
	}
	else
	{
		removeNode(pgePointers.toReturn);
		// checkHeight(pgePointers.rootTiny);
	}
	if (size + 32 <= pgePointers.toReturn->allocatedSize)
	{
		addNode(&pgePointers.rootTiny, splitMemory(size));
		// ft_printf("Out of add\n");
	}
		// printTree2(pgePointers.rootTiny);
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

int	checkLimit(size_t size)
{
	struct rlimit limit;

	getrlimit(RLIMIT_DATA, &limit);
	if (size > limit.rlim_max)
		return 0;
	return 1;
}