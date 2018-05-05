#include "malloc.h"

void*	getNewPage(t_mem_ctrl* pageMemCtrl, size_t size)
{
	void* tmp;

	tmp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == MAP_FAILED)
	{
		pgePointers.errors |= MMAP_BAD_ALLOC;
		return NULL;
	}
	if (pageMemCtrl)
	{
		pageMemCtrl->pageAddr = tmp;
		pageMemCtrl->allocatedSize = pgePointers.pageSize;
		pageMemCtrl->free = TRUE;
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

	if (pgePointers.memCtrlSizeLeft < MEM_CTRL_SIZE)
	{
		pgePointers.memCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
		if (!(pgePointers.lastTinyCtrl->next = getNewPage(NULL, pgePointers.memCtrlSizeLeft)))
			return NULL;
		newMemCtrl = pgePointers.lastTinyCtrl->next;
		// if (!newMemCtrl->next = getNewPage(NULL, )
	}
	else
		newMemCtrl = (char*)pgePointers.lastTinyCtrl + MEM_CTRL_SIZE;
	newMemCtrl->prev = memCtrlSplited;
	newMemCtrl->next = memCtrlSplited->next;
	memCtrlSplited->next ? memCtrlSplited->next->prev = newMemCtrl : 0;
	memCtrlSplited->next = newMemCtrl;
	pgePointers.lastTinyCtrl = newMemCtrl;
	pgePointers.memCtrlSizeLeft -= MEM_CTRL_SIZE;
	newMemCtrl->free = TRUE;

	return newMemCtrl;
}

// TODO: IMPORTANT : CHECK TO REFACTOR createNewMemCtrl && splitMemory
// 		ADD a setMemCtrl function, to use in createNewMemCtrl and popLostMemCtrl

/** 
 ** @brief  Split memory pointed by pgePointers.toReturn
 ** @note	pgePointer.toReturn contains the address to split
 **			If there are lost memCtrl due to block fusion, re use first of it
 **			Else, call @createNewMemCtrl(@address to split)
 **			Set the headers value size of splited header and new header.
 **			Set the new header->pageAddr, toReturn->pageAddr doesn't change.
 **
 ** @param  size: 
 ** @retval	None
 **/
t_mem_ctrl*	splitMemory(size_t size)
{
	t_mem_ctrl* newMemCtrl;

	// if (!(newMemCtrl = popLostMemCtrl(pgePointers.toReturn)))
		if (!(newMemCtrl = createNewMemCtrl(pgePointers.toReturn)))
			return NULL;
	newMemCtrl->prev = pgePointers.toReturn;
	newMemCtrl->next = pgePointers.toReturn->next;
	newMemCtrl->allocatedSize = pgePointers.toReturn->allocatedSize - size;
	pgePointers.toReturn->next ? pgePointers.toReturn->next->prev = newMemCtrl : 0;
	pgePointers.toReturn->next = newMemCtrl;
	pgePointers.toReturn->requiredSize = pgePointers.size;
	pgePointers.toReturn->allocatedSize = size;
	pgePointers.toReturn->free = FALSE;
	return newMemCtrl;
}
