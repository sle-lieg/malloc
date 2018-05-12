#include "malloc.h"

//TODO: shit free, just implemented to check if malloc works
//			implement it with multithreading
void	ft_free(void* ptr)
{
	if (!ptr)
		return;
	if (pgePointers.firstTinyCtrl && (char*)ptr >= pgePointers.firstTinyCtrl->pageAddr
											&& (char*)ptr <= pgePointers.lastTinyCtrl->pageAddr)
		checkTiny(ptr);
	// if (ptr >= pgePointers.firstSmallCtrl && ptr <= pgePointers.lastSmallCtrl)
	// 	checkSmall(ptr);
	// if (ptr >= pgePointers.firstLargeCtrl && ptr <= pgePointers.lastLargeCtrl)
	// 	checkLarge(ptr);
}

void	checkTiny(char* ptr)
{
	t_mem_ctrl* tmp;

	tmp = pgePointers.firstTinyCtrl;
	while (tmp)
	{
		if (tmp->pageAddr == ptr)
		{
			freeMemCtrl(tmp);
			return;
		}
		tmp = tmp->next;
	}
}

void	freeMemCtrl(t_mem_ctrl* ptr)
{
	ptr->free = TRUE;
	ptr->requiredSize = 0;
	if (ptr->next && ptr->next->free == 1 && ptr->pageSerie == ptr->next->pageSerie)
	{
		ptr->allocatedSize += ptr->next->allocatedSize;
		linkLostPrevNext(ptr);
		pushToLost(ptr->next);
	}
	if (ptr->prev && ptr->prev->free == 1 && ptr->pageSerie == ptr->prev->pageSerie)
	{
		ptr = ptr->prev;
		ptr->allocatedSize += ptr->next->allocatedSize;
		linkLostPrevNext(ptr);
		pushToLost(ptr->next);
	}
	addNode(&pgePointers.rootTiny, ptr);
}

void linkLostPrevNext(t_mem_ctrl* ptr)
{
	if (ptr->next->next)
		ptr->next->next->prev = ptr;
	ptr->next = ptr->next->next;
}

void	pushToLost(t_mem_ctrl* ptr)
{
	removeNode(ptr);
	ptr->pageAddr = NULL;
	ptr->allocatedSize = 0;
	ptr->requiredSize = 0;
	ptr->pageSerie = 0;
	ptr->height = 0;
	ptr->prev = NULL;
	ptr->next = pgePointers.lost_mem_ctrl;
	pgePointers.lost_mem_ctrl = ptr;
}

// void	freeMemCtrl(t_mem_ctrl* ptr)
// {
// 	ptr->free = 1;
// 	ptr->requiredSize = 0;

// 	if (ptr->prev && ptr->prev->free == 1 && ptr->pageSerie == ptr->prev->pageSerie)
// 	{
// 		ptr = ptr->prev;
// 	}

// 	if (ptr->next && ptr->next->free == 1 && ptr->pageSerie == ptr->next->pageSerie)
// 	{
// 		pushToLost(ptr->next);
// 		ptr->allocatedSize += ptr->next->allocatedSize;
// 		if (ptr->next->next)
// 			ptr->next->next->prev = ptr;
// 		ptr->next = ptr->next->next;
// 	}
// 	if (ptr->prev && ptr->prev->free == 1 && ptr->pageSerie == ptr->prev->pageSerie)
// 	{
// 		pushToLost(ptr->prev);
// 		ptr->allocatedSize += ptr->prev->allocatedSize;
// 		if (ptr->prev->prev)
// 			ptr->prev->prev->next = ptr;
// 		ptr->prev = ptr->prev->prev;
// 	}
// }
