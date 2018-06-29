/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_remover.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:29:41 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 10:45:19 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	remove_node(t_mem_ctrl *node)
{
	if (!node->lchild && !node->rchild)
		remove_leaf(node);
	else if (node->lchild && node->rchild)
		remove_parent_of_children(node);
	else
		remove_orphan(node);
	recursive_balance(node->father);
	node->father = NULL;
	node->lchild = NULL;
	node->rchild = NULL;
}

void	remove_leaf(t_mem_ctrl *node)
{
	if (g_pges_ctrl.root == node)
		g_pges_ctrl.root = NULL;
	else if (node == node->father->lchild)
	{
		node->father->lchild = NULL;
		node->father->height = node->father->rchild ? node->father->height : 1;
	}
	else
	{
		node->father->rchild = NULL;
		node->father->height = node->father->lchild ? node->father->height : 1;
	}
}

void	remove_parent_of_children(t_mem_ctrl *node)
{
	t_mem_ctrl *tmp;

	if (node->lchild->height >= node->rchild->height)
	{
		tmp = get_predecessor(node, node->lchild);
		if (node->lchild != tmp)
			swap_nodes(tmp, node);
		tmp->height = max_height(tmp->lchild, tmp->rchild) + 1;
	}
	else
	{
		tmp = get_successor(node, node->rchild);
		if (node->rchild != tmp)
			swap_nodes(tmp, node);
		tmp->height = max_height(tmp->lchild, tmp->rchild) + 1;
	}
	if (node == g_pges_ctrl.root)
		g_pges_ctrl.root = tmp;
}

void	remove_orphan(t_mem_ctrl *node)
{
	if (node->lchild)
		link_nodes(node->father, node->lchild);
	else
		link_nodes(node->father, node->rchild);
	if (node == g_pges_ctrl.root)
		g_pges_ctrl.root = (node->lchild ? node->lchild : node->rchild);
}

void	recursive_balance(t_mem_ctrl *node)
{
	if (!node)
		return ;
	node->height = max_height(node->lchild, node->rchild) + 1;
	check_balance(node);
	recursive_balance(node->father);
}
