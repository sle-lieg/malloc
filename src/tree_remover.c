#include "malloc.h"

void	remove_node(t_mem_ctrl* node)
{
	// ft_printf("REMOVE NODE %p\n", node);
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

void	remove_leaf(t_mem_ctrl* node)
{
	if (pges_ctrl.root == node)
		pges_ctrl.root = NULL;
	else if (node == node->father->lchild)
	{
		node->father->lchild = NULL;
		// node->father->height = node->father->rchild ? node->father->height : 1;
		node->father->mem_flags &= 0xFFFF0000 + (node->father->rchild ? get_height(node->father) : 1);
	}
	else
	{
		node->father->rchild = NULL;
		// node->father->height = node->father->lchild ? node->father->height : 1;
		node->father->mem_flags &= 0xFFFF0000 + (node->father->lchild ? get_height(node->father) : 1);
	}
}

void	remove_parent_of_children(t_mem_ctrl* node)
{
	t_mem_ctrl* tmp;

	if (get_height(node->lchild) >= get_height(node->rchild))
	{
		tmp = get_predecessor(node, node->lchild);
		if (node->lchild != tmp)
		{
			swap_nodes(tmp, node);
		}
		// tmp->mem_flags &= 0xFFFF0000 + max_height(tmp->lchild, tmp->rchild) + 1;
	}
	else
	{
		tmp = get_successor(node, node->rchild);
		if (node->rchild != tmp)
		{
			swap_nodes(tmp, node);
		}
		// tmp->mem_flags &= 0xFFFF0000 + max_height(tmp->lchild, tmp->rchild) + 1;
	}
	tmp->mem_flags &= 0xFFFF0000 + max_height(tmp->lchild, tmp->rchild) + 1;
	if (node == pges_ctrl.root)
		pges_ctrl.root = tmp;
	// replaceIfRoot(node, tmp);
}

// void	remove_parent_of_children(t_mem_ctrl* node)
// {
// 	t_mem_ctrl* tmp;

// 	if (node->lchild->height >= node->rchild->height)
// 	{
// 		tmp = get_predecessor(node, node->lchild);
// 		if (node->lchild != tmp)
// 		{
// 			swap_nodes(tmp, node);
// 		}
// 		tmp->height = max_height(tmp->lchild, tmp->rchild) + 1;
// 	}
// 	else
// 	{
// 		tmp = get_successor(node, node->rchild);
// 		if (node->rchild != tmp)
// 		{
// 			swap_nodes(tmp, node);
// 		}
// 		tmp->height = max_height(tmp->lchild, tmp->rchild) + 1;
// 	}
// 	if (node == pges_ctrl.root)
// 		pges_ctrl.root = tmp;
// 	// replaceIfRoot(node, tmp);
// }

void	remove_orphan(t_mem_ctrl* node)
{
	if (node->lchild)
		link_nodes(node->father, node->lchild);
	else
		link_nodes(node->father, node->rchild);
	if (node == pges_ctrl.root)
		pges_ctrl.root = (node->lchild ? node->lchild : node->rchild);
	// replaceIfRoot(node, (node->lchild ? node->lchild : node->rchild));
	// if (node == pges_ctrl.rootTiny)
	// 	pges_ctrl.rootTiny = node->lchild ? node->lchild : node->rchild;
}

void	recursive_balance(t_mem_ctrl* node)
{
	// ft_printf("REC BALANCE %p\n", node);
	if (!node)
		return;
	node->mem_flags &= 0xFFFF0000 + max_height(node->lchild, node->rchild) + 1;
	check_balance(node);
	recursive_balance(node->father);
}

// void	recursive_balance(t_mem_ctrl* node)
// {
// 	// ft_printf("REC BALANCE %p\n", node);
// 	if (!node)
// 		return;
// 	node->height = max_height(node->lchild, node->rchild) + 1;
// 	check_balance(node);
// 	recursive_balance(node->father);
// }
