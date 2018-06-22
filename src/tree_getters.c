#include "malloc.h"

static void	link_right_child(t_mem_ctrl* father, t_mem_ctrl* child)
{
	if (father)
		father->rchild = child;
   if (child)
   	child->father = father;
}

static void	link_left_child(t_mem_ctrl* father, t_mem_ctrl* child)
{
	if (father)
		father->lchild = child;
   if (child)
   	child->father = father;
}

t_mem_ctrl*	get_predecessor(t_mem_ctrl* to_replace, t_mem_ctrl* node)
{
	// ft_printf("PREDECESSOR\n");
	t_mem_ctrl* to_return;

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
			return to_return;
		}
		if (node->lchild)
		{
			link_nodes(node->father, node->lchild);
		}
		else
			node->father->rchild = NULL;
	}
	return to_return;
}

t_mem_ctrl*	get_successor(t_mem_ctrl* to_replace, t_mem_ctrl* node)
{
	// ft_printf("SUCCESSOR\n");
	t_mem_ctrl* to_return;

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
			return to_return;
		}
		if (node->rchild)
			link_nodes(node->father, node->rchild);
		else
			node->father->lchild = NULL;
	}
	return to_return;
}

t_mem_ctrl*	find_mem_ctrl(t_mem_ctrl* node, char* addr_to_free)
{
	if (!node)
		return (NULL);
	if (addr_to_free < node->addr)
		return (find_mem_ctrl(node->lchild, addr_to_free));
	if (addr_to_free > node->addr)
		return (find_mem_ctrl(node->rchild, addr_to_free));
	return (node);
}
// **********************************

// void	FRClinkNodes(t_mem_ctrl* father, t_mem_ctrl* child)
// {
// 	if (father)
// 		father->rchild = child;
//    if (child)
//    	child->father = father;
// }

// void	FLClinkNodes(t_mem_ctrl* father, t_mem_ctrl* child)
// {
// 	if (father)
// 		father->lchild = child;
//    if (child)
//    	child->father = father;
// }

// t_mem_ctrl*	getInOrderPredecessor(t_mem_ctrl* to_replace, t_mem_ctrl* node)
// {
// 	t_mem_ctrl* toReturn;

// 	toReturn = node;
// 	if (node == toReplace->lchild && !node->rchild)
// 	{
// 		FRClinkNodes(node, node->father->rchild);
// 		linkNodes(node->father->father, node);
// 	}
// 	else
// 	{
// 		if (node->rchild)
// 		{
// 			toReturn = getInOrderPredecessor(toReplace, node->rchild);
// 			node->height = max_height(node->lchild, node->rchild) + 1;
// 			check_balance(node);
// 			return toReturn;
// 		}
// 		if (node->lchild)
// 		{
// 			linkNodes(node->father, node->lchild);
// 		}
// 		else
// 			node->father->rchild = NULL;
// 	}
// 	return toReturn;
// }

// t_mem_ctrl*	getInOrderSuccessor(t_mem_ctrl* toReplace, t_mem_ctrl* node)
// {
// 	t_mem_ctrl* toReturn;

// 	toReturn = node;
// 	if (node == toReplace->rchild && !node->lchild)
// 	{
// 		FLClinkNodes(node, node->father->lchild);
// 		linkNodes(node->father->father, node);
// 	}
// 	else
// 	{
// 		if (node->lchild)
// 		{
// 			toReturn = getInOrderSuccessor(toReplace, node->lchild);
// 			node->height = max_height(node->lchild, node->rchild) + 1;
// 			check_balance(node);
// 			return toReturn;
// 		}
// 		if (node->rchild)
// 			linkNodes(node->father, node->rchild);
// 		else
// 			node->father->lchild = NULL;
// 	}
// 	return toReturn;
// }
