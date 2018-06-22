/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_rotations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:55:03 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/22 09:01:15 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void  rotate_left(t_mem_ctrl* node)
{
	ft_printf("ROT LEFT\n");
	t_mem_ctrl* tmp;

	tmp = node->rchild;
	node->rchild = tmp ? tmp->lchild : NULL;
	if (tmp)
	{
		tmp->lchild ? tmp->lchild->father = node : 0;
		tmp->lchild = node;
	}
	if (node->father)
	{
		if (node == node->father->lchild)
			node->father->lchild = tmp;
		else
			node->father->rchild = tmp;
	}
	tmp ? tmp->father = node->father : 0;
	node->father = tmp;
	node->height = max_height(node->lchild, node->rchild) + 1;
	tmp ? tmp->height = max_height(tmp->lchild, tmp->rchild) + 1 : 0;
}

void	rotate_right(t_mem_ctrl* node)
{
	ft_printf("ROT RIGHT\n");	
	t_mem_ctrl* tmp;

	tmp = node->lchild;
	node->lchild = tmp ? tmp->rchild : NULL;
	if (tmp)
	{
		tmp->rchild ? tmp->rchild->father = node : 0;
		tmp->rchild = node;
	}
	if (node->father)
	{
		if (node == node->father->lchild)
			node->father->lchild = tmp;
		else
			node->father->rchild = tmp;
	}
	tmp ? tmp->father = node->father : 0;
	node->father = tmp;
	node->height = max_height(node->lchild, node->rchild) + 1;
	tmp ? tmp->height = max_height(tmp->lchild, tmp->rchild) + 1 : 0;
}
