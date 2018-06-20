#include "malloc.h"

//TODO: shit free, just implemented to check if malloc works
//			implement it with multithreading
void	free(void* ptr)
{
	// if (!pgePointers.count)
		ft_printf("Free(%p)\n", ptr);
	if (!ptr)
		return;
	if (!findMemCtrl(pgePointers.firstTinyCtrl, ptr))
		if (!findMemCtrl(pgePointers.firstSmallCtrl, ptr))
			if (!findLargeMemCtrl(pgePointers.firstLargeCtrl, ptr))
				return;
	// show_alloc_mem();
	// pgePointers.count++;
	// if (!pgePointers.count)
	// {
		// printAll();
	// 	printTree2(pgePointers.rootTiny);
	// }
	// checkGoodHeight(pgePointers.rootTiny);
}

int	findMemCtrl(t_mem_ctrl* tmp, void* ptr)
{
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->pageAddr == ptr && !tmp->free)
		{
			freeMemCtrl(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	findLargeMemCtrl(t_mem_ctrl* tmp, void* ptr)
{
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->pageAddr == ptr && !tmp->free)
		{
			if (pgePointers.firstLargeCtrl == tmp)
				pgePointers.firstLargeCtrl = tmp->next;
			else
				tmp->prev->next = tmp->next;
			munmap(tmp->pageAddr, tmp->allocatedSize);
			pushToLost(tmp);
			// freeMemCtrl(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	freeMemCtrl(t_mem_ctrl* ptr)
{
	t_mem_ctrl* tmp;

	ptr->free = TRUE;
	ptr->requiredSize = 0;
	while (ptr->next && ptr->next->free == 1 && ptr->pageSerie == ptr->next->pageSerie)
	{
		// if (!pgePointers.count)
		// 	ft_printf("\nLink freed next\n", ptr);
		tmp = ptr->next;
		removeNode(tmp);
		linkLostPrevNext(ptr);
		pushToLost(tmp);
	}
	while (ptr->prev && ptr->prev->free == 1 && ptr->pageSerie == ptr->prev->pageSerie)
	{
		// if (!pgePointers.count)
		// 	ft_printf("Link freed prev\n", ptr);
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
