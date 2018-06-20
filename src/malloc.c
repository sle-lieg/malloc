#include "malloc.h"

void*	malloc(size_t size)
{
	// pgePointers.count++;
 	// if (!pgePointers.count)
		// ft_printf("MALLOC(%lu)\n", size);
	// ft_printf("Malloc(%lu): MEM_CTRL_SIZE=%lu\n", size, pgePointers.tinyCtrlSizeLeft);
	if (!checkLimit(size))
		return NULL;
	pgePointers.toReturn = NULL;
	pgePointers.pageSize = getpagesize();
	size = size ? size : 16;
	size = (size % MEM_ALIGN) ?
		((size >> MEM_ALIGN_SHIFT) << MEM_ALIGN_SHIFT) + MEM_ALIGN : size;
	if (size <= TINY_MAX)
		handleTiny(size);
	else if (size <= SMALL_MAX)
		handleSmall(size);
	else
		handleLarge(size);
	if (pgePointers.errors)
		return NULL;
	// pgePointers.count++;

	// if (!pgePointers.count)
	// {
	// 	printAll();
	// 	printTree2(pgePointers.rootTiny);
	// }
	// show_alloc_mem();

	return pgePointers.toReturn->pageAddr;
}

// void*	malloc(size_t size)
// {
// 	// pgePointers.count++;
//  	// if (!pgePointers.count)
// 		// ft_printf("MALLOC(%lu)\n", size);
// 	// ft_printf("Malloc(%lu): MEM_CTRL_SIZE=%lu\n", size, pgePointers.tinyCtrlSizeLeft);
// 	if (!checkLimit(size))
// 		return NULL;
// 	pgePointers.toReturn = NULL;
// 	pgePointers.pageSize = getpagesize();
// 	pgePointers.size = size; // TODO: need to keep real size ?
// 	size = size ? size : 16;
// 	size = (size % MEM_ALIGN) ?
// 		((size >> MEM_ALIGN_SHIFT) << MEM_ALIGN_SHIFT) + MEM_ALIGN : size;
// 	if (size <= TINY_MAX)
// 		handleTiny(size);
// 	else if (size <= SMALL_MAX)
// 		handleSmall(size);
// 	else
// 		handleLarge(size);
// 	if (pgePointers.errors)
// 		return NULL;
// 	// pgePointers.count++;

// 	// if (!pgePointers.count)
// 	// {
// 	// 	printAll();
// 	// 	printTree2(pgePointers.rootTiny);
// 	// }
// 	// show_alloc_mem();

// 	return pgePointers.toReturn->pageAddr;
// }

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
	ft_printf("TINY\n");
	if (!pgePointers.firstTinyCtrl)
		if (!initRootTiny(size))
			return;
	findFreeBlock(pgePointers.rootTiny, size);

	if (!pgePointers.toReturn) // not enough place on the heap, need to allocate a new page.
	{
		if (!(pgePointers.toReturn = createNewTinyMemCtrl(getLastLink(pgePointers.firstTinyCtrl))))
			return;
		pgePointers.toReturn->free = FALSE;
		getNewPage(pgePointers.toReturn, size);
		if (pgePointers.errors)
			return;
	}
	else
		removeNode(pgePointers.toReturn);
	if (size + 32 <= pgePointers.toReturn->allocatedSize)
		addNode(&pgePointers.rootTiny, splitMemory(size));
}

void	handleSmall(size_t size)
{
	ft_printf("SMALL\n");	
	if (!pgePointers.firstSmallCtrl)
		if (!initRootSmall(size))
			return;
	findFreeBlock(pgePointers.rootSmall, size);

	if (!pgePointers.toReturn) // not enough place on the heap, need to allocate a new page.
	{
		if (!(pgePointers.toReturn = createNewSmallMemCtrl(getLastLink(pgePointers.firstSmallCtrl))))
			return;
		pgePointers.toReturn->free = FALSE;
		getNewPage(pgePointers.toReturn, size);
		if (pgePointers.errors)
			return;
	}
	else
		removeNode(pgePointers.toReturn);
	if (size + 256 <= pgePointers.toReturn->allocatedSize)
		addNode(&pgePointers.rootSmall, splitMemory(size));
}

void	handleLarge(size_t size)
{
	ft_printf("LARGE\n");
	if (!pgePointers.firstLargeCtrl)
		if (!initRootLarge(size))
			return;
	// findFreeBlock(pgePointers.rootLarge, size);

	// if (!pgePointers.toReturn) // not enough place on the heap, need to allocate a new page.
	// {
		if (!(pgePointers.toReturn = createNewLargeMemCtrl(getLastLink(pgePointers.firstLargeCtrl))))
			return;
		pgePointers.toReturn->free = FALSE;
		getNewPage(pgePointers.toReturn, size);
		if (pgePointers.errors)
			return;
	// }
	// else
	// 	removeNode(pgePointers.toReturn);
	// if (size + 32 <= pgePointers.toReturn->allocatedSize)
	// 	addNode(&pgePointers.rootSmall, splitMemory(size));
}

int	checkLimit(size_t size)
{
	struct rlimit limit;

	getrlimit(RLIMIT_DATA, &limit);
	if (size > limit.rlim_max)
		return 0;
	return 1;
}
