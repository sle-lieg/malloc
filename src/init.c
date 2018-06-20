/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 09:06:08 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/19 14:33:16 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	initRootTiny()
{
	pgePointers.tinyCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
	if (!(pgePointers.firstTinyCtrl = getNewPage(NULL, pgePointers.tinyCtrlSizeLeft)) ||
												!(getNewPage(pgePointers.firstTinyCtrl, TINY_ZONE)))
		return 0;
	pgePointers.firstTinyCtrl->next = NULL;
	pgePointers.tinyCtrlSizeLeft -= MEM_CTRL_SIZE;
	pgePointers.lastTinyCtrl = pgePointers.firstTinyCtrl;
	pgePointers.rootTiny = pgePointers.firstTinyCtrl;

	return 1;
}

int	initRootSmall()
{
	pgePointers.smallCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
	if (!(pgePointers.firstSmallCtrl = getNewPage(NULL, pgePointers.smallCtrlSizeLeft)) ||
												!(getNewPage(pgePointers.firstSmallCtrl, SMALL_ZONE)))
		return 0;
	pgePointers.firstSmallCtrl->next = NULL;
	pgePointers.smallCtrlSizeLeft -= MEM_CTRL_SIZE;
	pgePointers.lastSmallCtrl = pgePointers.firstSmallCtrl;
	pgePointers.rootSmall = pgePointers.firstSmallCtrl;

	return 1;
}

int	initRootLarge()
{
	pgePointers.largeCtrlSizeLeft = pgePointers.pageSize * NB_PAGES;
	// if (!(pgePointers.firstLargeCtrl = getNewPage(NULL, pgePointers.largeCtrlSizeLeft)) ||
	// 											!(getNewPage(pgePointers.firstLargeCtrl, size)))
	if (!(pgePointers.firstLargeCtrl = getNewPage(NULL, pgePointers.largeCtrlSizeLeft)))
		return 0;
	pgePointers.firstLargeCtrl->next = NULL;
	// pgePointers.largeCtrlSizeLeft -= MEM_CTRL_SIZE;
	pgePointers.lastLargeCtrl = pgePointers.firstLargeCtrl;
	// pgePointers.rootLarge = pgePointers.firstLargeCtrl;

	return 1;
}
// TODO: remove or clean it
t_mem_ctrl*	getLastLink(t_mem_ctrl* ctrl)
{
	while (ctrl->next)
		ctrl = ctrl->next;
	return ctrl;
}
