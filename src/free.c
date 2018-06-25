#include "malloc.h"

void	free(void* ptr)
{
	if (pges_ctrl.debug > 0)
		ft_printf("FREE(%p)", ptr);
	t_mem_ctrl* to_free;

	if (!ptr)
		return;
	to_free = find_mem_ctrl(pges_ctrl.root, ptr);
	if (to_free)
	{
		if (pges_ctrl.debug > 0)
			ft_printf(" FOUND ", ptr);
		if (to_free->size <= SMALL_MAX)
			free_mem_ctrl(to_free);
		else
		{
			remove_node(to_free);
			push_to_lost(to_free);
		}
	}
	assert(pges_ctrl.fst_tiny->prev == NULL);
	if (pges_ctrl.debug > 0)
	{
		show_alloc_mem();
		printTree2(pges_ctrl.root);
		print_empty();
	}
}

void	free_mem_ctrl(t_mem_ctrl* to_free)
{
	int size;

	size = to_free->size;
	to_free->free = TRUE;
	if (!to_free->prev || (to_free->prev &&
	(!to_free->prev->free || to_free->prev->pge_id != to_free->pge_id)))
	{
		if (to_free->size <= TINY_MAX)
			add_to_free(&pges_ctrl.free_tiny, to_free);
		else
			add_to_free(&pges_ctrl.free_small, to_free);
	}
	while (to_free->prev && to_free->prev->free &&
			to_free->prev->pge_id == to_free->pge_id)
		to_free = to_free->prev;
	while (to_free->next && to_free->next->free &&
		to_free->next->pge_id == to_free->pge_id)
	{
		to_free->size += to_free->next->size;
		remove_node(to_free->next);
		if (size <= TINY_MAX)
			remove_from_free(pges_ctrl.free_tiny, to_free->next);
		else
			remove_from_free(pges_ctrl.free_small, to_free->next);
		push_to_lost(to_free->next);
	}
}

void	push_to_lost(t_mem_ctrl* ptr)
{
	if (pges_ctrl.debug > 0)
		ft_printf("LOST %p ", ptr);
	ptr->addr = NULL;
	ptr->size = 0;
	ptr->pge_id = 0;
	ptr->height = 0;
	ptr->father = NULL;
	ptr->lchild = NULL;
	ptr->rchild = NULL;
	if (ptr->prev)
	{
		if (ptr == pges_ctrl.lst_tiny)
			pges_ctrl.lst_tiny = pges_ctrl.lst_tiny->prev;
		if (ptr == pges_ctrl.lst_small)
			pges_ctrl.lst_small = pges_ctrl.lst_small->prev;
		ptr->prev->next = ptr->next;
	}
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	ptr->next = pges_ctrl.lost_mem_ctrl;
	ptr->prev = NULL;
	pges_ctrl.lost_mem_ctrl = ptr;
}

// void	free_mem_ctrl(t_mem_ctrl* to_free)
// {
// 	to_free->free = TRUE;
// 	if (to_free->prev && (!to_free->prev->free ||
// 		to_free->prev->pge_id != to_free->pge_id))
// 	{
// 		ft_printf("prev not free so add ! ");
// 		if (to_free->size <= TINY_MAX)
// 			add_to_free(&pges_ctrl.free_tiny, to_free);
// 		else
// 			add_to_free(&pges_ctrl.free_small, to_free);
// 	}
// 	if (to_free->size <= TINY_MAX)
// 		free_tiny(to_free);
// 	else
// 		free_small(to_free);
// }

// void	free_tiny(t_mem_ctrl* to_free)
// {
// 	while (to_free->prev && to_free->prev->free &&
// 			to_free->prev->pge_id == to_free->pge_id)
// 	{
// 		ft_printf(" BACK ! ");
// 		to_free = to_free->prev;
// 	}
// 	while (to_free->next && to_free->next->free &&
// 		to_free->next->pge_id == to_free->pge_id)
// 	{
// 		ft_printf(" MERGING ! ");
// 		to_free->size += to_free->next->size;
// 		remove_node(to_free->next);
// 		remove_from_free(pges_ctrl.free_tiny, to_free->next);
// 		push_to_lost(to_free->next);
// 	}
// }

// void	free_small(t_mem_ctrl* to_free)
// {
// 	while (to_free->prev && to_free->prev->free &&
// 			to_free->prev->pge_id == to_free->pge_id)
// 	{
// 		ft_printf(" BACK ! ");
// 		to_free = to_free->prev;
// 	}
// 	while (to_free->next && to_free->next->free &&
// 		to_free->next->pge_id == to_free->pge_id)
// 	{
// 		ft_printf(" MERGING ! ");
// 		to_free->size += to_free->next->size;
// 		remove_node(to_free->next);
// 		remove_from_free(pges_ctrl.free_small, to_free->next);
// 		push_to_lost(to_free->next);
// 	}
// }

// int	findMemCtrl(t_mem_ctrl* tmp, void* ptr)
// {
// 	if (!tmp)
// 		return (0);
// 	while (tmp)
// 	{
// 		if (tmp->pageAddr == ptr && !tmp->free)
// 		{
// 			freeMemCtrl(tmp);
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	findLargeMemCtrl(t_mem_ctrl* tmp, void* ptr)
// {
// 	if (!tmp)
// 		return (0);
// 	while (tmp)
// 	{
// 		if (tmp->pageAddr == ptr && !tmp->free)
// 		{
// 			if (pges_ctrl.firstLargeCtrl == tmp)
// 				pges_ctrl.firstLargeCtrl = tmp->next;
// 			else
// 				tmp->prev->next = tmp->next;
// 			munmap(tmp->pageAddr, tmp->allocatedSize);
// 			pushToLost(tmp);
// 			// freeMemCtrl(tmp);
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// void	freeMemCtrl(t_mem_ctrl* ptr)
// {
// 	t_mem_ctrl* tmp;

// 	ptr->free = TRUE;
// 	ptr->requiredSize = 0;
// 	while (ptr->next && ptr->next->free == 1 && ptr->pageSerie == ptr->next->pageSerie)
// 	{
// 		// if (!pges_ctrl.count)
// 		// 	ft_printf("\nLink freed next\n", ptr);
// 		tmp = ptr->next;
// 		removeNode(tmp);
// 		linkLostPrevNext(ptr);
// 		pushToLost(tmp);
// 	}
// 	while (ptr->prev && ptr->prev->free == 1 && ptr->pageSerie == ptr->prev->pageSerie)
// 	{
// 		// if (!pges_ctrl.count)
// 		// 	ft_printf("Link freed prev\n", ptr);
// 		tmp = ptr;
// 		ptr = ptr->prev;
// 		removeNode(ptr);
// 		linkLostPrevNext(ptr);
// 		pushToLost(tmp);
// 	}
// 	addNode(&pges_ctrl.rootTiny, ptr);
// }

// void linkLostPrevNext(t_mem_ctrl* ptr)
// {
// 	ptr->allocatedSize += ptr->next->allocatedSize;
// 	if (ptr->next->next)
// 		ptr->next->next->prev = ptr;
// 	ptr->next = ptr->next->next;
// }

// void	pushToLost(t_mem_ctrl* ptr)
// {
// 	ptr->pageAddr = NULL;
// 	ptr->allocatedSize = 0;
// 	ptr->requiredSize = 0;
// 	ptr->pageSerie = 0;
// 	ptr->height = 0;
// 	ptr->father = NULL;	
// 	ptr->lchild = NULL;
// 	ptr->rchild = NULL;
// 	ptr->prev = NULL;
// 	ptr->next = pges_ctrl.lost_mem_ctrl;
// 	pges_ctrl.lost_mem_ctrl = ptr;
// }
