/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:22:20 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/28 23:26:46 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	link_right_child(t_mem_ctrl *father, t_mem_ctrl *child)
{
	if (father)
		father->rchild = child;
	if (child)
		child->father = father;
}

static void	link_left_child(t_mem_ctrl *father, t_mem_ctrl *child)
{
	if (father)
		father->lchild = child;
	if (child)
		child->father = father;
}

t_mem_ctrl	*get_predecessor(t_mem_ctrl *to_replace, t_mem_ctrl *node)
{
	t_mem_ctrl *to_return;

	to_return = node;
	if (node == to_replace->lchild && !node->rchild)
	{
		link_right_child(node, node->father->rchild);
		link_nodes(node->father->father, node);
	}
	else
	{
		if (node->rchild)
		{
			to_return = get_predecessor(to_replace, node->rchild);
			node->height = max_height(node->lchild, node->rchild) + 1;
			check_balance(node);
			return (to_return);
		}
		if (node->lchild)
			link_nodes(node->father, node->lchild);
		else
			node->father->rchild = NULL;
	}
	return (to_return);
}

t_mem_ctrl	*get_successor(t_mem_ctrl *to_replace, t_mem_ctrl *node)
{
	t_mem_ctrl *to_return;

	to_return = node;
	if (node == to_replace->rchild && !node->lchild)
	{
		link_left_child(node, node->father->lchild);
		link_nodes(node->father->father, node);
	}
	else
	{
		if (node->lchild)
		{
			to_return = get_successor(to_replace, node->lchild);
			node->height = max_height(node->lchild, node->rchild) + 1;
			check_balance(node);
			return (to_return);
		}
		if (node->rchild)
			link_nodes(node->father, node->rchild);
		else
			node->father->lchild = NULL;
	}
	return (to_return);
}

t_mem_ctrl	*find_mem_ctrl(t_mem_ctrl *node, char *addr_to_free)
{
	if (!node)
		return (NULL);
	if (addr_to_free < node->addr)
		return (find_mem_ctrl(node->lchild, addr_to_free));
	if (addr_to_free > node->addr)
		return (find_mem_ctrl(node->rchild, addr_to_free));
	return (node);
}
