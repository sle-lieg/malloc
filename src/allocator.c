#include "malloc.h"



// void*	getNewPage(t_mem_ctrl* pageMemCtrl, size_t size)
// {
// 	void* tmp;
// 	size_t totPagesSize;

// 	totPagesSize = (size % pges_ctrl.pageSize) ?
// 		((size >> 12) << 12) + pges_ctrl.pageSize : size;
// 	tmp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
// 	if (tmp == MAP_FAILED)
// 	{
// 		pges_ctrl.errors |= MMAP_BAD_ALLOC;
// 		return NULL;
// 	}
// 	if (pageMemCtrl)
// 	{
// 		pageMemCtrl->pageAddr = tmp;
// 		pageMemCtrl->allocatedSize = totPagesSize;
// 		pageMemCtrl->pageSerie = ++pges_ctrl.pages_id;
// 	}
// 	return tmp;
// }

// TODO: VERIFIER ALIGNEMENT DES MEM_CTRL
/** 
 ** @brief	Generate new empty header.
 ** @note	Create a new header, and link it to the header memCtrlSplited.
 **			Doesn't point to any mapped address, just return it in state.
 **			If not enough memory left to create a new one, alloc NB_PAGES * PAGE_SIZE
 **			new pages for headers.
 ** @param  memCtrlSplited: 
 ** @retval	t_mem_ctrl*
 **/
// t_mem_ctrl*	createNewTinyMemCtrl(t_mem_ctrl* memCtrlSplited)
// {
// 	t_mem_ctrl* newMemCtrl;

// 	if (!(newMemCtrl = popLostMemCtrl()))
// 	{
// 		// ft_printf(" NO POP ");
// 		if (pges_ctrl.tinyCtrlSizeLeft < MEM_CTRL_SIZE)
// 		{
// 			// ft_printf(" NO MEM ");
// 			pges_ctrl.tinyCtrlSizeLeft = pges_ctrl.pageSize * NB_PAGES;
// 			if (!(newMemCtrl = getNewPage(NULL, pges_ctrl.tinyCtrlSizeLeft)))
// 				return NULL;
// 		}
// 		else
// 			newMemCtrl = pges_ctrl.lastTinyCtrl + 1;
// 		pges_ctrl.lastTinyCtrl = newMemCtrl;
// 		pges_ctrl.tinyCtrlSizeLeft -= MEM_CTRL_SIZE;
// 	}
// 	setMemCtrl(newMemCtrl, memCtrlSplited);

// 	return newMemCtrl;
// }

// t_mem_ctrl*	createNewSmallMemCtrl(t_mem_ctrl* memCtrlSplited)
// {
// 	t_mem_ctrl* newMemCtrl;

// 	if (!(newMemCtrl = popLostMemCtrl()))
// 	{
// 		// ft_printf(" NO POP ");
// 		if (pges_ctrl.smallCtrlSizeLeft < MEM_CTRL_SIZE)
// 		{
// 			// ft_printf(" NO MEM ");
// 			pges_ctrl.smallCtrlSizeLeft = pges_ctrl.pageSize * NB_PAGES;
// 			if (!(newMemCtrl = getNewPage(NULL, pges_ctrl.smallCtrlSizeLeft)))
// 				return NULL;
// 		}
// 		else
// 			newMemCtrl = pges_ctrl.lastSmallCtrl + 1;
// 		pges_ctrl.lastSmallCtrl = newMemCtrl;
// 		pges_ctrl.smallCtrlSizeLeft -= MEM_CTRL_SIZE;
// 	}
// 	setMemCtrl(newMemCtrl, memCtrlSplited);

// 	return newMemCtrl;
// }

// t_mem_ctrl*	createNewLargeMemCtrl(t_mem_ctrl* memCtrlSplited)
// {
// 	t_mem_ctrl* newMemCtrl;

// 	if (!(newMemCtrl = popLostMemCtrl()))
// 	{
// 		// ft_printf(" NO POP ");
// 		if (pges_ctrl.largeCtrlSizeLeft < MEM_CTRL_SIZE)
// 		{
// 			// ft_printf(" NO MEM ");
// 			pges_ctrl.largeCtrlSizeLeft = pges_ctrl.pageSize * NB_PAGES;
// 			if (!(newMemCtrl = getNewPage(NULL, pges_ctrl.largeCtrlSizeLeft)))
// 				return NULL;
// 		}
// 		else
// 		{
// 			if (pges_ctrl.firstLargeCtrl->next)
// 				newMemCtrl = pges_ctrl.lastLargeCtrl + 1;
// 			else
// 				newMemCtrl = pges_ctrl.firstLargeCtrl;
// 		}
// 		pges_ctrl.lastLargeCtrl = newMemCtrl;
// 		pges_ctrl.largeCtrlSizeLeft -= MEM_CTRL_SIZE;
// 	}
// 	if (newMemCtrl != memCtrlSplited)
// 		setMemCtrl(newMemCtrl, memCtrlSplited);

// 	return newMemCtrl;
// }
// // t_mem_ctrl*	createNewMemCtrl(t_mem_ctrl* memCtrlSplited)
// // {
// // 	t_mem_ctrl* newMemCtrl;

// // 	if (!(newMemCtrl = popLostMemCtrl()))
// // 	{
// // 		// ft_printf(" NO POP ");
// // 		if (pges_ctrl.tinyCtrlSizeLeft < MEM_CTRL_SIZE)
// // 		{
// // 			// ft_printf(" NO MEM ");
// // 			pges_ctrl.tinyCtrlSizeLeft = pges_ctrl.pageSize * NB_PAGES;
// // 			if (!(newMemCtrl = getNewPage(NULL, pges_ctrl.tinyCtrlSizeLeft)))
// // 				return NULL;
// // 		}
// // 		else
// // 			newMemCtrl = pges_ctrl.lastTinyCtrl + 1;
// // 		pges_ctrl.lastTinyCtrl = newMemCtrl;
// // 		pges_ctrl.tinyCtrlSizeLeft -= MEM_CTRL_SIZE;
// // 	}
// // 	setMemCtrl(newMemCtrl, memCtrlSplited);

// // 	return newMemCtrl;
// // }

// t_mem_ctrl*	splitMemory(size_t size)
// {
// 	t_mem_ctrl* newMemCtrl;

// 	if (size <= TINY_MAX)
// 	{
// 		if (!(newMemCtrl = createNewTinyMemCtrl(pges_ctrl.toReturn)))
// 			return NULL;
// 	}
// 	else
// 	{
// 		if (!(newMemCtrl = createNewSmallMemCtrl(pges_ctrl.toReturn)))
// 			return NULL;
// 	}
// 	newMemCtrl->allocatedSize = pges_ctrl.toReturn->allocatedSize - size;
// 	newMemCtrl->pageAddr = pges_ctrl.toReturn->pageAddr + size;
// 	pges_ctrl.toReturn->requiredSize = pges_ctrl.size;
// 	pges_ctrl.toReturn->allocatedSize = size;
// 	pges_ctrl.toReturn->father = NULL; //TODO: reseting to NULL ??
// 	pges_ctrl.toReturn->lchild = NULL;
// 	pges_ctrl.toReturn->rchild = NULL;
// 	pges_ctrl.toReturn->free = FALSE;
// 	return newMemCtrl;
// }

// void	setMemCtrl(t_mem_ctrl* newMemCtrl, t_mem_ctrl* memCtrlSplited)
// {
// 	newMemCtrl->prev = memCtrlSplited;
// 	newMemCtrl->next = memCtrlSplited->next;
// 	memCtrlSplited->next ? memCtrlSplited->next->prev = newMemCtrl : 0;
// 	memCtrlSplited->next = newMemCtrl;
// 	newMemCtrl->free = TRUE;
// 	newMemCtrl->pageSerie = memCtrlSplited->pageSerie;
// }
