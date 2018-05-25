#include "malloc.h"

//TODO: shit free, just implemented to check if malloc works
//			implement it with multithreading
void	free(void* ptr)
{
	ft_printf("Free(%p)\n", ptr);
	if (!ptr)
		return;
	// if (pgePointers.firstTinyCtrl && (char*)ptr >= pgePointers.firstTinyCtrl->pageAddr
	// 										&& (char*)ptr <= pgePointers.lastTinyCtrl->pageAddr)
	checkTiny(ptr);
	// if (ptr >= pgePointers.firstSmallCtrl && ptr <= pgePointers.lastSmallCtrl)
	// 	checkSmall(ptr);
	// if (ptr >= pgePointers.firstLargeCtrl && ptr <= pgePointers.lastLargeCtrl)
	// 	checkLarge(ptr);
	printAll();
	printTree2(pgePointers.rootTiny);
}

void	checkTiny(void* ptr)
{
	t_mem_ctrl* tmp;

	tmp = pgePointers.firstTinyCtrl;
	while (tmp)
	{
		if (tmp->pageAddr == ptr && !tmp->free)
		{
			// ft_printf("Free(tmp[%p]{%lu}->addr[%p])\n", tmp, tmp->allocatedSize, ptr);
			freeMemCtrl(tmp);
			// printTree2(pgePointers.rootTiny);	
			return;
		}
		tmp = tmp->next;
	}
}

// void	freeMemCtrl(t_mem_ctrl* ptr)
// {
// 	t_mem_ctrl* tmp;

// 	ptr->free = TRUE;
// 	ptr->requiredSize = 0;
// 	if (ptr->next && ptr->next->free == 1 && ptr->pageSerie == ptr->next->pageSerie)
// 	{
// 		// ft_printf("Link freed next\n", ptr);
// 		tmp = ptr->next;
// 		removeNode(tmp);
// 		tmp->father ? checkBalance(tmp->father) : 0;
// 		linkLostPrevNext(ptr);
// 		pushToLost(tmp);
// 	}
// 	if (ptr->prev && ptr->prev->free == 1 && ptr->pageSerie == ptr->prev->pageSerie)
// 	{
// 		// ft_printf("Link freed prev\n", ptr);
// 		tmp = ptr;
// 		ptr = ptr->prev;
// 		linkLostPrevNext(ptr);
// 		pushToLost(tmp);
// 	}
// 	else
// 		addNode(&pgePointers.rootTiny, ptr);
// }

void	freeMemCtrl(t_mem_ctrl* ptr)
{
	t_mem_ctrl* tmp;

	ptr->free = TRUE;
	ptr->requiredSize = 0;
	if (ptr->next && ptr->next->free == 1 && ptr->pageSerie == ptr->next->pageSerie)
	{
		ft_printf("Link freed next\n", ptr);
		tmp = ptr->next;
		removeNode(tmp);
		linkLostPrevNext(ptr);
		pushToLost(tmp);
	}
	if (ptr->prev && ptr->prev->free == 1 && ptr->pageSerie == ptr->prev->pageSerie)
	{
		ft_printf("Link freed prev\n", ptr);
		tmp = ptr;
		ptr = ptr->prev;
		removeNode(ptr);
		linkLostPrevNext(ptr);
		pushToLost(tmp);
	}
	addNode(&pgePointers.rootTiny, ptr);
}

void linkLostPrevNext(t_mem_ctrl* ptr)
{
	ptr->allocatedSize += ptr->next->allocatedSize;
	if (ptr->next->next)
		ptr->next->next->prev = ptr;
	ptr->next = ptr->next->next;
	if (pgePointers.lastTinyCtrl == ptr)
	{
		ft_printf(" DECR %p ", pgePointers.lastTinyCtrl);
		pgePointers.lastTinyCtrl--;
		ft_printf(" -> %p ", pgePointers.lastTinyCtrl);		
	}
}

void	pushToLost(t_mem_ctrl* ptr)
{
	ptr->pageAddr = NULL;
	ptr->allocatedSize = 0;
	ptr->requiredSize = 0;
	ptr->pageSerie = 0;
	ptr->height = 0;
	ptr->father = NULL;	
	ptr->lchild = NULL;
	ptr->rchild = NULL;
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
