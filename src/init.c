/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 09:06:08 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 11:30:06 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	init_tiny(void)
{
	g_pges_ctrl.fst_tiny = g_pges_ctrl.header_pge++;
	if (!(g_pges_ctrl.fst_tiny->addr = create_new_page(g_pges_ctrl.tiny_zone)))
		return (0);
	g_pges_ctrl.fst_tiny->free = TRUE;
	g_pges_ctrl.fst_tiny->size = g_pges_ctrl.tiny_zone;
	g_pges_ctrl.fst_tiny->pge_id = ++g_pges_ctrl.pages_id;
	g_pges_ctrl.lst_tiny = g_pges_ctrl.fst_tiny;
	g_pges_ctrl.free_tiny = g_pges_ctrl.fst_tiny;
	add_node(g_pges_ctrl.fst_tiny);
	return (1);
}

int	init_small(void)
{
	g_pges_ctrl.fst_small = g_pges_ctrl.header_pge++;
	g_pges_ctrl.fst_small->addr = create_new_page(g_pges_ctrl.small_zone);
	if (!g_pges_ctrl.fst_small->addr)
		return (0);
	g_pges_ctrl.fst_small->free = TRUE;
	g_pges_ctrl.fst_small->size = g_pges_ctrl.small_zone;
	g_pges_ctrl.fst_small->pge_id = ++g_pges_ctrl.pages_id;
	g_pges_ctrl.lst_small = g_pges_ctrl.fst_small;
	g_pges_ctrl.free_small = g_pges_ctrl.fst_small;
	add_node(g_pges_ctrl.fst_small);
	return (1);
}
