/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:28:18 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 15:19:06 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		extend_header_pge(void)
{
	g_pges_ctrl.header_pge = mmap(NULL, getpagesize() * NB_PAGES,\
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (g_pges_ctrl.header_pge == MAP_FAILED)
		return (0);
	g_pges_ctrl.header_pge_limit = (t_mem_ctrl*)((char*)g_pges_ctrl.header_pge \
	+ (getpagesize() * NB_PAGES));
	ft_bzero(g_pges_ctrl.header_pge, (char*)g_pges_ctrl.header_pge_limit\
	- (char*)g_pges_ctrl.header_pge);
	return (1);
}

void	*create_new_page(size_t size)
{
	void	*p;

	p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (p == MAP_FAILED)
	{
		g_pges_ctrl.errors |= MMAP_BAD_ALLOC;
		return (NULL);
	}
	return (p);
}

int		extend_heap(t_mem_ctrl *last_mctrl, size_t size)
{
	if (!(g_pges_ctrl.ret = pop_lost_mem_ctrl()))
	{
		if (g_pges_ctrl.header_pge + 1 > g_pges_ctrl.header_pge_limit)
			if (!(extend_header_pge()))
				return (0);
		g_pges_ctrl.ret = g_pges_ctrl.header_pge++;
	}
	last_mctrl->next = g_pges_ctrl.ret;
	g_pges_ctrl.ret->prev = last_mctrl;
	if (!(g_pges_ctrl.ret->addr = create_new_page(size)))
		return (0);
	g_pges_ctrl.ret->size = size;
	g_pges_ctrl.ret->free = FALSE;
	g_pges_ctrl.ret->pge_id = ++g_pges_ctrl.pages_id;
	return (1);
}

size_t	align_memory16(size_t size)
{
	if (!size)
		size = MEM_ALIGN_16;
	else if (size % MEM_ALIGN_16)
		size = ((size >> ALIGN_16_SHIFT) << ALIGN_16_SHIFT) + MEM_ALIGN_16;
	return (size);
}

size_t	align_memory_page(size_t size)
{
	if (size % getpagesize())
		size = ((size >> ALIGN_PAGE_SHIFT) << ALIGN_PAGE_SHIFT) + getpagesize();
	return (size);
}
