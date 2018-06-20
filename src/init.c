/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 09:06:08 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/20 17:25:53 by sle-lieg         ###   ########.fr       */
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

int	init_tiny()
{
	pges_ctrl.fst_tiny = pges_ctrl.header_pge++;
	assert((char*)pges_ctrl.fst_tiny == (char*)(pges_ctrl.header_pge) - sizeof(t_mem_ctrl));
	if (!(pges_ctrl.fst_tiny->addr = create_new_page(pges_ctrl.tiny_zone)))
		return (0);
	pges_ctrl.fst_tiny->free = TRUE;
	pges_ctrl.fst_tiny->size = pges_ctrl.tiny_zone;
	pges_ctrl.fst_tiny->pge_id = ++pges_ctrl.pages_id;
	pges_ctrl.lst_tiny = pges_ctrl.fst_tiny;
	pges_ctrl.free_tiny = pges_ctrl.fst_tiny;
	add_node(pges_ctrl.fst_tiny);
	// ft_printf("First_tiny: %p\nLast_tiny: %p\nFree_tiny: %p\n", pges_ctrl.fst_tiny, pges_ctrl.lst_tiny, pges_ctrl.free_tiny);
	// ft_printf("addr: %p\nnext: %p\nprev: %p\n", pges_ctrl.fst_tiny->addr, pges_ctrl.fst_tiny->next, pges_ctrl.fst_tiny->prev);
	return 1;
}

int	init_small()
{
	pges_ctrl.fst_small = pges_ctrl.header_pge++;
	if (!(pges_ctrl.fst_small->addr = create_new_page(pges_ctrl.small_zone)))
		return (0);
	pges_ctrl.fst_small->free = TRUE;
	pges_ctrl.fst_small->size = pges_ctrl.small_zone;
	pges_ctrl.fst_small->pge_id = ++pges_ctrl.pages_id;
	pges_ctrl.lst_small = pges_ctrl.fst_small;
	pges_ctrl.free_small = pges_ctrl.fst_small;
	add_node(pges_ctrl.fst_small);
	return 1;
}

// int	initRootLarge()
// {
// 	pges_ctrl.largeCtrlSizeLeft = pges_ctrl.pageSize * NB_PAGES;
// 	// if (!(pges_ctrl.firstLargeCtrl = getNewPage(NULL, pges_ctrl.largeCtrlSizeLeft)) ||
// 	// 											!(getNewPage(pges_ctrl.firstLargeCtrl, size)))
// 	if (!(pges_ctrl.firstLargeCtrl = getNewPage(NULL, pges_ctrl.largeCtrlSizeLeft)))
// 		return 0;
// 	pges_ctrl.firstLargeCtrl->next = NULL;
// 	// pges_ctrl.largeCtrlSizeLeft -= MEM_CTRL_SIZE;
// 	pges_ctrl.lastLargeCtrl = pges_ctrl.firstLargeCtrl;
// 	// pges_ctrl.rootLarge = pges_ctrl.firstLargeCtrl;

// 	return 1;
// }
// TODO: remove or clean it
