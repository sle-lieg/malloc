#include "malloc.h"

void	removeNode(t_mem_ctrl* node)
{
	if (!node->lchild && !node->rchild)
		removeLeaf(node);
	else if (node->lchild && node->rchild)
		removeParentOfChildren(node);
	else
		removeParentOfOrphan(node);
}

void	removeLeaf(t_mem_ctrl* node)
{
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = NULL;
	else if (node->allocatedSize <= node->father->allocatedSize)
		node->father->lchild = NULL;
	else
		node->father->rchild = NULL;
}

void	removeParentOfChildren(t_mem_ctrl* node)
{
	t_mem_ctrl* tmp;

	if (node->lchild->height >= node->rchild->height)
	{
		tmp = getInOrderPredecessor(node->lchild);
		if (node->lchild != tmp)
			swapNodes(tmp, node);
	}
	else
	{
		tmp = getInOrderSuccessor(node->rchild);
		if (node->rchild != tmp)
			swapNodes(tmp, node);		
	}
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = tmp;
}

void	removeParentOfOrphan(t_mem_ctrl* node)
{
	if (node->lchild)
		linkNodes(node->father, node->lchild);
	else
		linkNodes(node->father, node->rchild);
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = node->lchild ? node->lchild : node->rchild;
}
