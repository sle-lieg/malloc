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

void	splitMemory(size_t size)
{
	/*
		pgePointer.toReturn contains the rigth address to split
		call createNewMemCtrl(toReturn)
	*/
	t_mem_ctrl* memSplited;

	if (!(memSplited = createNewMemCtrl(pgePointer.toReturn))))
		return;
	memSplited->allocatedSize = pgePointer.toReturn->allocatedSize - size;
	pgePointer.toReturn->allocatedSize = size;
	pgePointer.toReturn->requiredSize = pgePointer.size;

	// Enlever toReturn de l' arbre.
	// Ajouter memSplited dans l' arbre.
	// Equilibrer l' arbre.
	
}

