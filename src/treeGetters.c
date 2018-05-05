#include "malloc.h"

t_mem_ctrl*	getInOrderPredecessor(t_mem_ctrl* node)
{
	if (!node->rchild)
	{
		linkNodes(node->father->father, node);
		linkNodes(node, node->father->rchild);
	}
	else
	{
		while (node->rchild)
			node = node->rchild;
		if (node->lchild)
			linkNodes(node->father, node->lchild);
		node->father->rchild = NULL;
	}
	return node;
}

t_mem_ctrl*	getInOrderSuccessor(t_mem_ctrl* node)
{
	if (!node->lchild)
	{
		linkNodes(node->father->father, node);
		linkNodes(node, node->father->lchild);
	}
	else
	{
		while (node->lchild)
			node = node->lchild;
		if (node->rchild)
			linkNodes(node->father, node->rchild);
		node->father->lchild = NULL;
	}
	return node;
}

int getHeight(t_mem_ctrl* node)
{
	return node ? node->height : 0;
}