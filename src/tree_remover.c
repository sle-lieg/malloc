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
		node->father->height = node->father->rchild ? node->father->height : 1;
	}
	else
	{
		node->father->rchild = NULL;
		node->father->height = node->father->lchild ? node->father->height : 1;
	}
}

void	remove_parent_of_children(t_mem_ctrl* node)
{
	t_mem_ctrl* tmp;

	if (node->lchild->height >= node->rchild->height)
	{
		tmp = get_predecessor(node, node->lchild);
		if (node->lchild != tmp)
		{
			swap_nodes(tmp, node);
		}
		tmp->height = max_height(tmp->lchild, tmp->rchild) + 1;
	}
	else
	{
		tmp = get_successor(node, node->rchild);
		if (node->rchild != tmp)
		{
			swap_nodes(tmp, node);
		}
		tmp->height = max_height(tmp->lchild, tmp->rchild) + 1;
	}
	if (node == pges_ctrl.root)
		pges_ctrl.root = tmp;
	// replaceIfRoot(node, tmp);
}

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
	node->height = max_height(node->lchild, node->rchild) + 1;
	check_balance(node);
	recursive_balance(node->father);
}

// ********************************************************************

// void	recursiveBalance(t_mem_ctrl* node)
// {
// 	int factor;

// 	if (!node)
// 		return;

// 	// ft_printf(" Recursive Balance ");

// 	node->height = maxHeight(node->lchild, node->rchild) + 1;
//    factor = getHeight(node->lchild) - getHeight(node->rchild);
// 	if (factor > 1)
// 	{
// 		if (checkBalance(node->lchild) >= 0)
// 			rotateRight(node);
// 		else
// 		{
// 			rotateLeft(node->lchild);
// 			rotateRight(node);
// 		}
// 	}
// 	else if (factor < -1)
// 	{
// 		if (checkBalance(node->rchild) <= 0)
// 			rotateLeft(node);
// 		else
// 		{
// 			rotateRight(node->rchild);
// 			rotateLeft(node);
// 		}
// 	}
// 	if (factor < -1 || factor > 1)
// 		replaceIfRoot(node, node->father);
// 	recursiveBalance(node->father);
// }

// void	removeNode(t_mem_ctrl* node)
// {
// 	// if (!pges_ctrl.count)
// 	// 	ft_printf("RemoveNode(%p)\n", node);
// 	if (!node->lchild && !node->rchild)
// 		removeLeaf(node);
// 	else if (node->lchild && node->rchild)
// 		removeParentOfChildren(node);
// 	else
// 		removeParentOfOrphan(node);
	
// 	recursiveBalance(node->father);

// 	node->free = FALSE;
// 	node->father = NULL;
// 	node->lchild = NULL;
// 	node->rchild = NULL;
// }

// void	removeLeaf(t_mem_ctrl* node)
// {
// 	// if (!pges_ctrl.count)
// 		// ft_printf("Remove : leaf %p, lchild %p, rchild %p, fath %p\n", node, node->lchild, node->rchild, node->father);
// 	if (replaceIfRoot(node, node->father))
// 		return;
// 	else if (node == node->father->lchild)
// 	{
// 	// if (!pges_ctrl.count)
// 	// 		ft_printf("Remove left leaf\n");
// 		node->father->lchild = NULL;
// 		node->father->height = node->father->rchild ? node->father->height : 1;
// 	}
// 	else if (node == node->father->rchild)
// 	{
// 		// if (!pges_ctrl.count)
// 		// 	ft_printf("Remove right leaf\n");
// 		node->father->rchild = NULL;
// 		node->father->height = node->father->lchild ? node->father->height : 1;
// 	}
// }

// void	removeParentOfChildren(t_mem_ctrl* node)
// {
// 	// if (!pges_ctrl.count)
// 	// 	ft_printf("Remove childrens\n");
// 	t_mem_ctrl* tmp;

// 	if (node->lchild->height >= node->rchild->height)
// 	{
// 		tmp = getInOrderPredecessor(node, node->lchild);
// 		if (node->lchild != tmp)
// 		{
// 			swapNodes(tmp, node);
// 		}
// 		tmp->height = maxHeight(tmp->lchild, tmp->rchild) + 1;
// 	}
// 	else
// 	{
// 		tmp = getInOrderSuccessor(node, node->rchild);
// 		if (node->rchild != tmp)
// 		{
// 			swapNodes(tmp, node);
// 		}
// 		tmp->height = maxHeight(tmp->lchild, tmp->rchild) + 1;
// 	}
// 	replaceIfRoot(node, tmp);
// }

// void	removeParentOfOrphan(t_mem_ctrl* node)
// {
// 	// if (!pges_ctrl.count)
// 	// 	ft_printf("Remove orphan\n");
// 	if (node->lchild)
// 		linkNodes(node->father, node->lchild);
// 	else
// 		linkNodes(node->father, node->rchild);
// 	replaceIfRoot(node, (node->lchild ? node->lchild : node->rchild));
// 	// if (node == pges_ctrl.rootTiny)
// 	// 	pges_ctrl.rootTiny = node->lchild ? node->lchild : node->rchild;
// }
