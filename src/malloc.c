/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 22:17:18 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/28 23:16:20 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	pges_ctrl.tiny_zone = (((TINY_MAX * 100) >> 12) << 12) + getpagesize();
	pges_ctrl.small_zone = (((SMALL_MAX * 100) >> 12) << 12) + getpagesize();
	pges_ctrl.ret = NULL;
	size = (size <= SMALL_MAX ? align_memory16(size) : align_memory_page(size));
	pthread_mutex_lock(&mutex_alloc);
	if (!pges_ctrl.header_pge ||
		pges_ctrl.header_pge + 1 > pges_ctrl.header_pge_limit)
	{
		if (!(extend_header_pge()))
		{
			pthread_mutex_unlock(&mutex_alloc);
			return (NULL);
		}
	}
	if (size <= TINY_MAX)
		handle_tiny(size);
	else if (size <= SMALL_MAX)
		handle_small(size);
	else
		handle_large(size);
	pthread_mutex_unlock(&mutex_alloc);
	if (pges_ctrl.errors)
		return (NULL);
	return (pges_ctrl.ret->addr);
}

void	handle_tiny(size_t size)
{
	if (!pges_ctrl.fst_tiny)
		if (!init_tiny())
			return;
	find_free_block(pges_ctrl.free_tiny, size);
	if (!pges_ctrl.ret)
	{
		if (!(extend_heap(pges_ctrl.lst_tiny, pges_ctrl.tiny_zone)))
			return;
		pges_ctrl.lst_tiny = pges_ctrl.ret;
	}
	if (pges_ctrl.ret->size - size >= 16)
	{
		split_memory(size);
		add_to_free(&pges_ctrl.free_tiny, pges_ctrl.ret->next);
		if (pges_ctrl.ret == pges_ctrl.lst_tiny)
			pges_ctrl.lst_tiny = pges_ctrl.ret->next;
	}
}

void	handle_small(size_t size)
{
	if (!pges_ctrl.fst_small)
		if (!init_small())
			return;
	find_free_block(pges_ctrl.free_small, size);
	if (!pges_ctrl.ret)
	{
		if (!(extend_heap(pges_ctrl.lst_small, pges_ctrl.small_zone)))
			return;
		pges_ctrl.lst_small = pges_ctrl.ret;
	}
	if (pges_ctrl.ret->size - size >= TINY_MAX)
	{
		split_memory(size);
		add_to_free(&pges_ctrl.free_small, pges_ctrl.ret->next);
		if (pges_ctrl.ret == pges_ctrl.lst_small)
			pges_ctrl.lst_small = pges_ctrl.ret->next;
	}
}

void	handle_large(size_t size)
{
	if (!(pges_ctrl.ret = pop_lost_mem_ctrl()))
		pges_ctrl.ret = pges_ctrl.header_pge++;
	if (!(pges_ctrl.ret->addr = create_new_page(size)))
		return;
	pges_ctrl.ret->size = size;
	add_node(pges_ctrl.ret);
	if (!pges_ctrl.fst_large)
	{
		pges_ctrl.fst_large = pges_ctrl.ret;
		pges_ctrl.lst_large = pges_ctrl.ret;
	}
	else
	{
		pges_ctrl.lst_large->next = pges_ctrl.ret;
		pges_ctrl.ret->prev = pges_ctrl.lst_large;
		pges_ctrl.lst_large = pges_ctrl.lst_large->next;
	}
}
