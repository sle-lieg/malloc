#include "malloc.h"

void	addNode(t_mem_ctrl** root, t_mem_ctrl* newNode)
{
	ft_printf("Add Node(%p)\n", newNode);
	if (!*root)
	{
		*root = newNode;
		newNode->height = 1;
	}
	else
		recursiveAdd(*root, newNode);
}

void	recursiveAdd(t_mem_ctrl* node, t_mem_ctrl* newNode)
{
	ft_printf("RecursiveAdd\n");	
	
	if (newNode->allocatedSize <= node->allocatedSize)
	{
		if (node->lchild)
			recursiveAdd(node->lchild, newNode);
		else
		{
			addLinks(node, newNode);
			newNode->height = 1;
			newNode->free = TRUE;			
		}
	}
	else
	{
		if (node->rchild)
			recursiveAdd(node->rchild, newNode);
		else
		{
			addLinks(node, newNode);
			newNode->height = 1;
			newNode->free = TRUE;
		}
	}
	// printTree2(pgePointers.rootTiny);
	// ft_printf("\n");
	checkBalance(node);
	node->height = maxHeight(node->lchild, node->rchild) + 1;
}