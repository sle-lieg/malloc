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
			newNode->height = node->height;			
		}
	}
	else
	{
		if (node->rchild)
			recursiveAdd(node->rchild, newNode);
		else
		{
			linkNodes(node, newNode);
			newNode->height = node->height;
		}
	}
	checkBalance(node);
	node->height = maxHeight(node->rchild, node->lchild) + 1;
}