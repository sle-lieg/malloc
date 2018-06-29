/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:55:09 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 10:45:19 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static	int	replace_if_root(t_mem_ctrl *node, t_mem_ctrl *new_root)
{
	if (g_pges_ctrl.root == node)
	{
		g_pges_ctrl.root = new_root;
		return (1);
	}
	return (0);
}

static int	get_height(t_mem_ctrl *node)
{
	return (node ? node->height : 0);
}

int			check_balance(t_mem_ctrl *node)
{
	int factor;

	factor = get_height(node->lchild) - get_height(node->rchild);
	if (factor > 1)
	{
		if (check_balance(node->lchild) < 0)
			rotate_left(node->lchild);
		rotate_right(node);
	}
	else if (factor < -1)
	{
		if (check_balance(node->rchild) > 0)
			rotate_right(node->rchild);
		rotate_left(node);
	}
	if (factor < -1 || factor > 1)
		replace_if_root(node, node->father);
	return (factor);
}

int			max_height(t_mem_ctrl *nod_a, t_mem_ctrl *nod_b)
{
	if (!nod_a && !nod_b)
		return (0);
	if (!nod_b)
		return (nod_a->height);
	if (!nod_a)
		return (nod_b->height);
	return ((nod_a->height > nod_b->height) ? nod_a->height : nod_b->height);
}
