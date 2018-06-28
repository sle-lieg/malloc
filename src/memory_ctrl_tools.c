/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_ctrl_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:24:48 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/28 13:53:34 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	find_free_block(t_mem_ctrl* block, size_t size)
{
	while (block)
	{
		if (block->size >= size)
		{
			assert(block->free == 1);
			pges_ctrl.ret = block;
			if (size <= TINY_MAX)
				remove_from_free(pges_ctrl.free_tiny, block);
			else
				remove_from_free(pges_ctrl.free_small, block);
			break;
		}
		block = block->next_free;
	}
}

t_mem_ctrl*	split_memory(size_t size)
{
	t_mem_ctrl* new_header;

	if (!(new_header = pop_lost_mem_ctrl()))
	{
		if (pges_ctrl.header_pge + 1 > pges_ctrl.header_pge_limit)
			if (!(extend_header_pge()))
				return (NULL);
		new_header = pges_ctrl.header_pge++;
		// assert(new_header == pges_ctrl.header_pge - 1);
	}
	// else
	// 	if (pges_ctrl.debug < 1 && pges_ctrl.debug < 1000)
	// 		ft_printf("POP HEADER %p | ", new_header);
	// if (pges_ctrl.debug < 1 && pges_ctrl.debug < 1000)
	// 	ft_printf("HEADER: f=%p lc=%p rc=%p\n", new_header->father, new_header->lchild, new_header->rchild);
	// assert(new_header->father == NULL);
	// assert(new_header->lchild == NULL);
	// assert(new_header->rchild == NULL);
	new_header->addr = pges_ctrl.ret->addr + size;
	new_header->size = pges_ctrl.ret->size - size;
	new_header->prev = pges_ctrl.ret;
	new_header->next = pges_ctrl.ret->next;
	new_header->pge_id = pges_ctrl.ret->pge_id;
	pges_ctrl.ret->size = size;
	if (pges_ctrl.ret->next)
		pges_ctrl.ret->next->prev = new_header;
	pges_ctrl.ret->next = new_header;
	add_node(new_header);
	return NULL; // TODO: useless
}

// TODO: try with push_front
void	add_to_free(t_mem_ctrl** free_head, t_mem_ctrl* new_header)
{
	t_mem_ctrl* tmp;

	tmp = *free_head;
	if (!tmp || (new_header->size <= tmp->size))
	{
		new_header->next_free = *free_head;
		*free_head = new_header;
	}
	else
	{
		while (tmp->next_free)
		{
			if (new_header->size <= tmp->next_free->size)
				break;
			tmp = tmp->next_free;
		}
		new_header->next_free = tmp->next_free;
		tmp->next_free = new_header;
	}
	new_header->free = TRUE;
}

void	remove_from_free(t_mem_ctrl* tmp, t_mem_ctrl* block)
{
	if (pges_ctrl.free_tiny == block)
		pges_ctrl.free_tiny = block->next_free;
	else if (pges_ctrl.free_small == block)
		pges_ctrl.free_small = block->next_free;
	else
	{
		while (tmp->next_free)
		{
			if (tmp->next_free == block)
			{
				tmp->next_free = block->next_free;
				break;
			}
			tmp = tmp->next_free;
		}
	}
	block->free = FALSE;
}

t_mem_ctrl* pop_lost_mem_ctrl()
{
	t_mem_ctrl* newMemCtrl;

	if (!pges_ctrl.lost_mem_ctrl)
		return NULL;
	newMemCtrl = pges_ctrl.lost_mem_ctrl;
	pges_ctrl.lost_mem_ctrl = pges_ctrl.lost_mem_ctrl->next;
	newMemCtrl->next = NULL;
	return newMemCtrl;
}
