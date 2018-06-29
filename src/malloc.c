/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 22:17:18 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 11:20:33 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	g_pges_ctrl.ret = NULL;
	g_pges_ctrl.tiny_zone = (((100 * TINY_MAX) >> 12) << 12) + getpagesize();
	g_pges_ctrl.small_zone = (((100 * SMALL_MAX) >> 12) << 12) + getpagesize();
	size = (size <= SMALL_MAX ? align_memory16(size) : align_memory_page(size));
	pthread_mutex_lock(&g_mutex_alloc);
	if (!g_pges_ctrl.header_pge ||
		g_pges_ctrl.header_pge + 1 > g_pges_ctrl.header_pge_limit)
	{
		if (!(extend_header_pge()))
		{
			pthread_mutex_unlock(&g_mutex_alloc);
			return (NULL);
		}
	}
	if (size <= TINY_MAX)
		handle_tiny(size);
	else if (size <= SMALL_MAX)
		handle_small(size);
	else
		handle_large(size);
	pthread_mutex_unlock(&g_mutex_alloc);
	if (g_pges_ctrl.errors)
		return (NULL);
	return (g_pges_ctrl.ret->addr);
}

void	handle_tiny(size_t size)
{
	if (!g_pges_ctrl.fst_tiny)
		if (!init_tiny())
			return ;
	find_free_block(g_pges_ctrl.free_tiny, size);
	if (!g_pges_ctrl.ret)
	{
		if (!(extend_heap(g_pges_ctrl.lst_tiny, g_pges_ctrl.tiny_zone)))
			return ;
		g_pges_ctrl.lst_tiny = g_pges_ctrl.ret;
	}
	if (g_pges_ctrl.ret->size - size >= 16)
	{
		split_memory(size);
		add_to_free(&g_pges_ctrl.free_tiny, g_pges_ctrl.ret->next);
		if (g_pges_ctrl.ret == g_pges_ctrl.lst_tiny)
			g_pges_ctrl.lst_tiny = g_pges_ctrl.ret->next;
	}
}

void	handle_small(size_t size)
{
	if (!g_pges_ctrl.fst_small)
		if (!init_small())
			return ;
	find_free_block(g_pges_ctrl.free_small, size);
	if (!g_pges_ctrl.ret)
	{
		if (!(extend_heap(g_pges_ctrl.lst_small, g_pges_ctrl.small_zone)))
			return ;
		g_pges_ctrl.lst_small = g_pges_ctrl.ret;
	}
	if (g_pges_ctrl.ret->size - size >= TINY_MAX)
	{
		split_memory(size);
		add_to_free(&g_pges_ctrl.free_small, g_pges_ctrl.ret->next);
		if (g_pges_ctrl.ret == g_pges_ctrl.lst_small)
			g_pges_ctrl.lst_small = g_pges_ctrl.ret->next;
	}
}

void	handle_large(size_t size)
{
	if (!(g_pges_ctrl.ret = pop_lost_mem_ctrl()))
		g_pges_ctrl.ret = g_pges_ctrl.header_pge++;
	if (!(g_pges_ctrl.ret->addr = create_new_page(size)))
		return ;
	g_pges_ctrl.ret->size = size;
	add_node(g_pges_ctrl.ret);
	if (!g_pges_ctrl.fst_large)
	{
		g_pges_ctrl.fst_large = g_pges_ctrl.ret;
		g_pges_ctrl.lst_large = g_pges_ctrl.ret;
	}
	else
	{
		g_pges_ctrl.lst_large->next = g_pges_ctrl.ret;
		g_pges_ctrl.ret->prev = g_pges_ctrl.lst_large;
		g_pges_ctrl.lst_large = g_pges_ctrl.lst_large->next;
	}
}
