#include "malloc.h"

void	addNode(t_mem_ctrl** root, t_mem_ctrl* newNode)
{
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
	if (newNode->allocatedSize <= node->allocatedSize)
	{
		if (node->lchild)
			recursiveAdd(node->lchild, newNode);
		else
		{
			linkNodes(node, newNode);
			newNode->height = 1;
			// newNode->height = node->height;			
		}
	}
	else
	{
		if (node->rchild)
			recursiveAdd(node->rchild, newNode);
		else
		{
			linkNodes(node, newNode);
			newNode->height = 1;
		}
	}
	node->height = maxHeight(node->lchild, node->rchild) + 1;
	checkBalance(node);
}