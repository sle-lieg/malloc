#include "malloc.h"

void	free(void* ptr)
{
	t_mem_ctrl* to_free;

	if (!ptr)
		return;
	pthread_mutex_lock(&mutex_alloc);
	to_free = find_mem_ctrl(pges_ctrl.root, ptr);
	if (to_free)
	{
		if (to_free->size <= SMALL_MAX)
			free_mem_ctrl(to_free);
		else
		{
			munmap(ptr, to_free->size);
			remove_node(to_free);
			push_to_lost(to_free);
		}
	}
	pthread_mutex_unlock(&mutex_alloc);
}

void	free_mem_ctrl(t_mem_ctrl* to_free)
{
	int size;

	size = to_free->size;
	to_free->free = TRUE;
	if (!to_free->prev || !to_free->prev->free || (to_free->prev->pge_id != to_free->pge_id))
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
		else if (ptr == pges_ctrl.lst_small)
			pges_ctrl.lst_small = pges_ctrl.lst_small->prev;
		else if (ptr == pges_ctrl.lst_large)
			pges_ctrl.lst_large = pges_ctrl.lst_large->prev;
		ptr->prev->next = ptr->next;
	}
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	if (ptr == pges_ctrl.fst_large)
		pges_ctrl.fst_large = ptr->next;
	ptr->next = pges_ctrl.lost_mem_ctrl;
	ptr->prev = NULL;
	pges_ctrl.lost_mem_ctrl = ptr;
}
