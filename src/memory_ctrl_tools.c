/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_ctrl_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:24:48 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 14:56:16 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		find_free_block(t_mem_ctrl *block, size_t size)
{
	while (block)
	{
		if (block->size >= size)
		{
			g_pges_ctrl.ret = block;
			if (size <= TINY_MAX)
				remove_from_free(g_pges_ctrl.free_tiny, block);
			else
				remove_from_free(g_pges_ctrl.free_small, block);
			break ;
		}
		block = block->next_free;
	}
}

void		split_memory(size_t size)
{
	t_mem_ctrl *new_header;

	if (!(new_header = pop_lost_mem_ctrl()))
	{
		if (g_pges_ctrl.header_pge + 1 > g_pges_ctrl.header_pge_limit)
			if (!(extend_header_pge()))
				return ;
		new_header = g_pges_ctrl.header_pge++;
	}
	new_header->addr = g_pges_ctrl.ret->addr + size;
	new_header->size = g_pges_ctrl.ret->size - size;
	new_header->prev = g_pges_ctrl.ret;
	new_header->next = g_pges_ctrl.ret->next;
	new_header->pge_id = g_pges_ctrl.ret->pge_id;
	g_pges_ctrl.ret->size = size;
	if (g_pges_ctrl.ret->next)
		g_pges_ctrl.ret->next->prev = new_header;
	g_pges_ctrl.ret->next = new_header;
	add_node(new_header);
}

void		add_to_free(t_mem_ctrl **free_head, t_mem_ctrl *new_header)
{
	t_mem_ctrl *tmp;

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
				break ;
			tmp = tmp->next_free;
		}
		new_header->next_free = tmp->next_free;
		tmp->next_free = new_header;
	}
	new_header->free = TRUE;
}

void		remove_from_free(t_mem_ctrl *tmp, t_mem_ctrl *block)
{
	if (g_pges_ctrl.free_tiny == block)
		g_pges_ctrl.free_tiny = block->next_free;
	else if (g_pges_ctrl.free_small == block)
		g_pges_ctrl.free_small = block->next_free;
	else
	{
		while (tmp->next_free)
		{
			if (tmp->next_free == block)
			{
				tmp->next_free = block->next_free;
				break ;
			}
			tmp = tmp->next_free;
		}
	}
	block->free = FALSE;
}

t_mem_ctrl	*pop_lost_mem_ctrl(void)
{
	t_mem_ctrl *new_mem_ctrl;

	if (!g_pges_ctrl.lost_mem_ctrl)
		return (NULL);
	new_mem_ctrl = g_pges_ctrl.lost_mem_ctrl;
	g_pges_ctrl.lost_mem_ctrl = g_pges_ctrl.lost_mem_ctrl->next;
	new_mem_ctrl->next = NULL;
	return (new_mem_ctrl);
}
