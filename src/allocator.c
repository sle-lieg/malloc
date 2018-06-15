#include "malloc.h"

void*	getNewPage(t_mem_ctrl* pageMemCtrl, size_t size)
{
	void* tmp;
	size_t totPagesSize;

	totPagesSize = (size % pgePointers.pageSize) ?
		((size >> 12) << 12) + pgePointers.pageSize : size;
	tmp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == MAP_FAILED)
	{
		pgePointers.errors |= MMAP_BAD_ALLOC;
		return NULL;
	}
	if (pageMemCtrl)
	{
		pageMemCtrl->pageAddr = tmp;
		pageMemCtrl->allocatedSize = totPagesSize;
		pageMemCtrl->pageSerie = ++pgePointers.pageSerieCount;
	}
	return tmp;
}

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
t_mem_ctrl*	createNewMemCtrl(t_mem_ctrl* memCtrlSplited)
{
	t_mem_ctrl* newMemCtrl;

	if (!(newMemCtrl = popLostMemCtrl()))
	{
		// ft_printf(" NO POP ");
		if (pgePointers.memCtrlSizeLeft < MEM_CTRL_SIZE)
		{
			// ft_printf(" NO MEM ");
			pgePointers.memCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
			if (!(newMemCtrl = getNewPage(NULL, pgePointers.memCtrlSizeLeft)))
				return NULL;
		}
		else
			newMemCtrl = pgePointers.lastTinyCtrl + 1;
		pgePointers.lastTinyCtrl = newMemCtrl;
		pgePointers.memCtrlSizeLeft -= MEM_CTRL_SIZE;
	}
	setMemCtrl(newMemCtrl, memCtrlSplited);

	return newMemCtrl;
}

t_mem_ctrl*	splitMemory(size_t size)
{
	t_mem_ctrl* newMemCtrl;

	if (!(newMemCtrl = createNewMemCtrl(pgePointers.toReturn)))
		return NULL;
	newMemCtrl->allocatedSize = pgePointers.toReturn->allocatedSize - size;
	newMemCtrl->pageAddr = pgePointers.toReturn->pageAddr + size;
	pgePointers.toReturn->requiredSize = pgePointers.size;
	pgePointers.toReturn->allocatedSize = size;
	pgePointers.toReturn->father = NULL; //TODO: reseting to NULL ??
	pgePointers.toReturn->lchild = NULL;
	pgePointers.toReturn->rchild = NULL;
	pgePointers.toReturn->free = FALSE;
	return newMemCtrl;
}

void	setMemCtrl(t_mem_ctrl* newMemCtrl, t_mem_ctrl* memCtrlSplited)
{
	newMemCtrl->prev = memCtrlSplited;
	newMemCtrl->next = memCtrlSplited->next;
	memCtrlSplited->next ? memCtrlSplited->next->prev = newMemCtrl : 0;
	memCtrlSplited->next = newMemCtrl;
	newMemCtrl->free = TRUE;
	newMemCtrl->pageSerie = memCtrlSplited->pageSerie;
}

t_mem_ctrl* popLostMemCtrl()
{
	t_mem_ctrl* newMemCtrl;

	if (!pgePointers.lost_mem_ctrl)
		return NULL;
	newMemCtrl = pgePointers.lost_mem_ctrl;
	pgePointers.lost_mem_ctrl = pgePointers.lost_mem_ctrl->next;
	newMemCtrl->next = NULL;
	return newMemCtrl;
}