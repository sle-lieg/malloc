/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:41:31 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/28 23:50:12 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	add_links(t_mem_ctrl *father, t_mem_ctrl *child)
{
	if (child->addr < father->addr)
		father->lchild = child;
	else
		father->rchild = child;
	child->father = father;
}

void	swap_nodes(t_mem_ctrl *predecessor, t_mem_ctrl *node)
{
	predecessor->lchild = node->lchild;
	predecessor->rchild = node->rchild;
	predecessor->father = node->father;
	node->lchild->father = predecessor;
	node->rchild->father = predecessor;
	if (node->father && node->father->lchild == node)
		node->father->lchild = predecessor;
	else if (node->father)
		node->father->rchild = predecessor;
}

void	link_nodes(t_mem_ctrl *father, t_mem_ctrl *child)
{
	if (father && child && father->lchild == child->father)
		father->lchild = child;
	else if (father)
		father->rchild = child;
	if (child)
		child->father = father;
}
