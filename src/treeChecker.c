#include "malloc.h"

void	findFreeBlock(t_mem_ctrl* node, size_t size)
{
	if (!node || pgePointers.toReturn)
		return;
	if (node->lchild && size < node->allocatedSize)
		findFreeBlock(node->lchild, size);
	if (size <= node->allocatedSize && !pgePointers.toReturn)
		pgePointers.toReturn = node;
	else if (node->rchild && !pgePointers.toReturn)
		findFreeBlock(node->rchild, size);
}

int	checkBalance(t_mem_ctrl* node)
{
	// if (!pgePointers.count)
	// 	ft_printf("CheckBalance\n");
   int factor;

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
		replaceIfRoot(node);
   return factor;
}

int	maxHeight(t_mem_ctrl* nodeA, t_mem_ctrl* nodeB)
{
	if (!nodeA && !nodeB)
		return 0;
	if (nodeA && !nodeB)
		return nodeA->height;
	else if (!nodeA && nodeB)
		return nodeB->height;
	return nodeA->height > nodeB->height ? nodeA->height : nodeB->height;
}

void	checkHeight(t_mem_ctrl* node)
{
	// ft_printf("CheckHeight\n");
	if (!node)
		return;
	checkHeight(node->lchild);
	checkHeight(node->rchild);
	node->height = maxHeight(node->lchild, node->rchild) + 1;
}
