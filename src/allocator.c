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
		pageMemCtrl->free = 1;
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
		newMemCtrl = pgePointers.lastTinyCtrl + MEM_CTRL_SIZE;
	newMemCtrl->prev = memCtrlSplited;
	memCtrlSplited->next = newMemCtrl;
	pgePointers.lastTinyCtrl = newMemCtrl;
	pgePointers.memCtrlSizeLeft -= MEM_CTRL_SIZE;
	newMemCtrl->free = 1;

	return newMemCtrl;
}

/** 
 ** @brief  Split memory pointed by pgePointers.toReturn
 ** @note	pgePointer.toReturn contains the address to split
 **			Call @createNewMemCtrl(@address to split)
 **			Set the headers value size of splited header and new header.
 **			Set the new header->pageAddr, toReturn->pageAddr doesn't change.
 **			
 ** @param  size: 
 ** @retval	None
 **/
void	splitMemory(size_t size)
{
	t_mem_ctrl* memSplited;

	if (!(memSplited = createNewMemCtrl(pgePointers.toReturn)))
		return;
	memSplited->allocatedSize = pgePointers.toReturn->allocatedSize - size;
	pgePointers.toReturn->allocatedSize = size;
	pgePointers.toReturn->requiredSize = pgePointers.size;

	// Enlever toReturn de l' arbre.
	// Ajouter memSplited dans l' arbre.
	// Equilibrer l' arbre.
	removeNode();
	insertNode(memSplited);	
}

