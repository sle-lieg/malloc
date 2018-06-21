/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:28:18 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/21 10:27:21 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	extend_header_pge()
{
	pges_ctrl.header_pge = mmap(NULL, getpagesize() * NB_PAGES, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (pges_ctrl.header_pge == MAP_FAILED)
		return (0);
	pges_ctrl.header_pge_limit = pges_ctrl.header_pge + (getpagesize() * NB_PAGES);
	assert((pges_ctrl.header_pge_limit - pges_ctrl.header_pge) == (getpagesize() * NB_PAGES));
	// ft_printf("Header zone: %p - %p len= %lu\n", pges_ctrl.header_pge, pges_ctrl.header_pge_limit, pges_ctrl.header_pge_limit - pges_ctrl.header_pge );
	return (1);
}

void*	create_new_page(size_t size)
{
	void* tmp;

	tmp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == MAP_FAILED)
	{
		pges_ctrl.errors |= MMAP_BAD_ALLOC;
		return NULL;
	}
	return tmp;
}

int	extend_heap(t_mem_ctrl* last_mctrl)
{
	if (!(pges_ctrl.ret = pop_lost_mem_ctrl()))
		pges_ctrl.ret = pges_ctrl.header_pge++;
	last_mctrl->next = pges_ctrl.ret;
	pges_ctrl.ret->prev = last_mctrl;
	if (!(pges_ctrl.ret->addr = create_new_page(pges_ctrl.tiny_zone)))
		return (0);
	pges_ctrl.ret->size = pges_ctrl.tiny_zone;
	pges_ctrl.ret->free = TRUE;
	pges_ctrl.ret->pge_id = ++pges_ctrl.pages_id;
	return (1);
}

int	checkLimit(size_t size)
{
	struct rlimit limit;

	getrlimit(RLIMIT_DATA, &limit);
	if (size > limit.rlim_max)
		return 0;
	return 1;
}

size_t align_memory(size_t size)
{
	if (!size)
		size = MEM_ALIGN;
	else if (size % MEM_ALIGN)
		size = ((size >> MEM_ALIGN_SHIFT) << MEM_ALIGN_SHIFT) + MEM_ALIGN;
	assert(size % MEM_ALIGN == 0);
	return size;
}
