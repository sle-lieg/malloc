#include "malloc.h"

void	recursiveBalance(t_mem_ctrl* node)
{
	int factor;

	if (!node)
		return;

	// ft_printf(" Recursive Balance ");

	node->height = maxHeight(node->lchild, node->rchild) + 1;
   factor = getHeight(node->lchild) - getHeight(node->rchild);
	if (factor > 1)
	{
		if (checkBalance(node->lchild) >= 0)
			rotateRight(node);
		else
		{
			rotateLeft(node->lchild);
			rotateRight(node);
		}
	}
	else if (factor < -1)
	{
		if (checkBalance(node->rchild) <= 0)
			rotateLeft(node);
		else
		{
			rotateRight(node->rchild);
			rotateLeft(node);
		}
	}
	if (factor < -1 || factor > 1)
		replaceIfRoot(node, node->father);
	recursiveBalance(node->father);
}

void	removeNode(t_mem_ctrl* node)
{
	// if (!pges_ctrl.count)
	// 	ft_printf("RemoveNode(%p)\n", node);
	if (!node->lchild && !node->rchild)
		removeLeaf(node);
	else if (node->lchild && node->rchild)
		removeParentOfChildren(node);
	else
		removeParentOfOrphan(node);
	
	recursiveBalance(node->father);

	node->free = FALSE;
	node->father = NULL;
	node->lchild = NULL;
	node->rchild = NULL;
}

void	removeLeaf(t_mem_ctrl* node)
{
	// if (!pges_ctrl.count)
		// ft_printf("Remove : leaf %p, lchild %p, rchild %p, fath %p\n", node, node->lchild, node->rchild, node->father);
	if (replaceIfRoot(node, node->father))
		return;
	else if (node == node->father->lchild)
	{
	// if (!pges_ctrl.count)
	// 		ft_printf("Remove left leaf\n");
		node->father->lchild = NULL;
		node->father->height = node->father->rchild ? node->father->height : 1;
	}
	else if (node == node->father->rchild)
	{
		// if (!pges_ctrl.count)
		// 	ft_printf("Remove right leaf\n");
		node->father->rchild = NULL;
		node->father->height = node->father->lchild ? node->father->height : 1;
	}
}

void	removeParentOfChildren(t_mem_ctrl* node)
{
	// if (!pges_ctrl.count)
	// 	ft_printf("Remove childrens\n");
	t_mem_ctrl* tmp;

	if (node->lchild->height >= node->rchild->height)
	{
		tmp = getInOrderPredecessor(node, node->lchild);
		if (node->lchild != tmp)
		{
			swapNodes(tmp, node);
		}
		tmp->height = maxHeight(tmp->lchild, tmp->rchild) + 1;
	}
	else
	{
		tmp = getInOrderSuccessor(node, node->rchild);
		if (node->rchild != tmp)
		{
			swapNodes(tmp, node);
		}
		tmp->height = maxHeight(tmp->lchild, tmp->rchild) + 1;
	}
	replaceIfRoot(node, tmp);
}

void	removeParentOfOrphan(t_mem_ctrl* node)
{
	// if (!pges_ctrl.count)
	// 	ft_printf("Remove orphan\n");
	if (node->lchild)
		linkNodes(node->father, node->lchild);
	else
		linkNodes(node->father, node->rchild);
	replaceIfRoot(node, (node->lchild ? node->lchild : node->rchild));
	// if (node == pges_ctrl.rootTiny)
	// 	pges_ctrl.rootTiny = node->lchild ? node->lchild : node->rchild;
}
