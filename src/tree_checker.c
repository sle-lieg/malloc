/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:55:09 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/26 16:09:42 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	check_balance(t_mem_ctrl* node)
{
	int factor;

	factor = get_height(node->lchild) - get_height(node->rchild);
	if (factor > 1)
	{
		if (check_balance(node->lchild) >= 0)
			rotate_right(node);
		else
		{
			rotate_left(node->lchild);
			rotate_right(node);
		}
	}
	else if (factor < -1)
	{
		if (check_balance(node->rchild) <= 0)
			rotate_left(node);
		else
		{
			rotate_right(node->rchild);
			rotate_left(node);
		}
	}
	if (factor < -1 || factor > 1)
		replace_if_root(node, node->father);
	return factor;
}

int	max_height(t_mem_ctrl* nodeA, t_mem_ctrl* nodeB)
{
	if (!nodeA && !nodeB)
		return 0;
	if (!nodeB)
		return nodeA->mem_flags & HEIGHT_M;
	if (!nodeA)
		return nodeB->mem_flags & HEIGHT_M;
	return (nodeA->mem_flags & HEIGHT_M) > (nodeB->mem_flags & HEIGHT_M) ? (nodeA->mem_flags & HEIGHT_M) : (nodeB->mem_flags & HEIGHT_M);
}

// int	max_height(t_mem_ctrl* nodeA, t_mem_ctrl* nodeB)
// {
// 	if (!nodeA && !nodeB)
// 		return 0;
// 	if (!nodeB)
// 		return nodeA->height;
// 	if (!nodeA)
// 		return nodeB->height;
// 	return nodeA->height > nodeB->height ? nodeA->height : nodeB->height;
// }

// void	check_height(t_mem_ctrl* node)
// {
// 	// ft_printf("CheckHeight\n");
// 	if (!node)
// 		return;
// 	check_height(node->lchild);
// 	check_height(node->rchild);
// 	node->height = max_height(node->lchild, node->rchild) + 1;
// }
