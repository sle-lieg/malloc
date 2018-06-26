/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 09:06:08 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/26 15:58:28 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	init_tiny()
{
	// ft_printf("INIT TINY\n");
	pges_ctrl.fst_tiny = pges_ctrl.header_pge++;
	// assert((char*)pges_ctrl.fst_tiny == (char*)(pges_ctrl.header_pge) - sizeof(t_mem_ctrl));
	// assert(pges_ctrl.fst_tiny->prev == NULL);
	// assert(pges_ctrl.fst_tiny->next == NULL);
	// assert(pges_ctrl.fst_tiny->next_free == NULL);
	// assert(pges_ctrl.fst_tiny->father == NULL);
	// assert(pges_ctrl.fst_tiny->lchild == NULL);
	// assert(pges_ctrl.fst_tiny->rchild == NULL);
	
	if (!(pges_ctrl.fst_tiny->addr = create_new_page(pges_ctrl.tiny_zone)))
		return (0);
	// pges_ctrl.fst_tiny->free = TRUE;
	pges_ctrl.fst_tiny->mem_flags |= FREE_M;
	
	pges_ctrl.fst_tiny->size = pges_ctrl.tiny_zone;
	// pges_ctrl.fst_tiny->pge_id = ++pges_ctrl.pages_id;
	pges_ctrl.fst_tiny->mem_flags |= (++pges_ctrl.pages_id << 16);
	
	pges_ctrl.lst_tiny = pges_ctrl.fst_tiny;
	pges_ctrl.free_tiny = pges_ctrl.fst_tiny;
	add_node(pges_ctrl.fst_tiny);
	// ft_printf("First_tiny: %p\nLast_tiny: %p\nFree_tiny: %p\n", pges_ctrl.fst_tiny, pges_ctrl.lst_tiny, pges_ctrl.free_tiny);
	// ft_printf("addr: %p\nnext: %p\nprev: %p\n", pges_ctrl.fst_tiny->addr, pges_ctrl.fst_tiny->next, pges_ctrl.fst_tiny->prev);
	return 1;
}

int	init_small()
{
	// ft_printf("INIT SMALL\n");
	
	pges_ctrl.fst_small = pges_ctrl.header_pge++;
	if (!(pges_ctrl.fst_small->addr = create_new_page(pges_ctrl.small_zone)))
		return (0);
	// pges_ctrl.fst_small->free = TRUE;
	pges_ctrl.fst_small->mem_flags |= FREE_M;

	pges_ctrl.fst_small->size = pges_ctrl.small_zone;
	// pges_ctrl.fst_small->pge_id = ++pges_ctrl.pages_id;
	pges_ctrl.fst_small->mem_flags |= (++pges_ctrl.pages_id << 16);
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
