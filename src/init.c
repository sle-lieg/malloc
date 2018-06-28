/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 09:06:08 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/28 12:21:14 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	init_tiny()
{
	pges_ctrl.fst_tiny = pges_ctrl.header_pge++;

	if (!(pges_ctrl.fst_tiny->addr = create_new_page(pges_ctrl.tiny_zone)))
		return (0);
	pges_ctrl.fst_tiny->free = TRUE;
	pges_ctrl.fst_tiny->size = pges_ctrl.tiny_zone;
	pges_ctrl.fst_tiny->pge_id = ++pges_ctrl.pages_id;
	pges_ctrl.lst_tiny = pges_ctrl.fst_tiny;
	pges_ctrl.free_tiny = pges_ctrl.fst_tiny;
	add_node(pges_ctrl.fst_tiny);
	return 1;
}

int	init_small()
{
	// ft_printf("INIT SMALL\n");
	
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
