/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 22:44:05 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 10:45:43 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	t_mem_ctrl *to_free;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex_alloc);
	to_free = find_mem_ctrl(g_pges_ctrl.root, ptr);
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
	pthread_mutex_unlock(&g_mutex_alloc);
}

void	free_mem_ctrl(t_mem_ctrl *to_f)
{
	int size;

	size = to_f->size;
	to_f->free = TRUE;
	if (!to_f->prev || !to_f->prev->free ||
		(to_f->prev->pge_id != to_f->pge_id))
	{
		if (to_f->size <= TINY_MAX)
			add_to_free(&g_pges_ctrl.free_tiny, to_f);
		else
			add_to_free(&g_pges_ctrl.free_small, to_f);
	}
	while (to_f->prev && to_f->prev->free && to_f->prev->pge_id == to_f->pge_id)
		to_f = to_f->prev;
	while (to_f->next && to_f->next->free && to_f->next->pge_id == to_f->pge_id)
	{
		to_f->size += to_f->next->size;
		remove_node(to_f->next);
		if (size <= TINY_MAX)
			remove_from_free(g_pges_ctrl.free_tiny, to_f->next);
		else
			remove_from_free(g_pges_ctrl.free_small, to_f->next);
		push_to_lost(to_f->next);
	}
}

void	push_to_lost(t_mem_ctrl *ptr)
{
	ptr->addr = NULL;
	ptr->size = 0;
	ptr->pge_id = 0;
	ptr->height = 0;
	ptr->father = NULL;
	ptr->lchild = NULL;
	ptr->rchild = NULL;
	ptr->next_free = NULL;
	if (ptr->prev)
	{
		if (ptr == g_pges_ctrl.lst_tiny)
			g_pges_ctrl.lst_tiny = g_pges_ctrl.lst_tiny->prev;
		else if (ptr == g_pges_ctrl.lst_small)
			g_pges_ctrl.lst_small = g_pges_ctrl.lst_small->prev;
		else if (ptr == g_pges_ctrl.lst_large)
			g_pges_ctrl.lst_large = g_pges_ctrl.lst_large->prev;
		ptr->prev->next = ptr->next;
	}
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	if (ptr == g_pges_ctrl.fst_large)
		g_pges_ctrl.fst_large = ptr->next;
	ptr->next = g_pges_ctrl.lost_mem_ctrl;
	ptr->prev = NULL;
	g_pges_ctrl.lost_mem_ctrl = ptr;
}
