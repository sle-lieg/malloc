#include "malloc.h"

void	FRClinkNodes(t_mem_ctrl* father, t_mem_ctrl* child)
{
	if (father)
		father->rchild = child;
   if (child)
   	child->father = father;
}

void	FLClinkNodes(t_mem_ctrl* father, t_mem_ctrl* child)
{
	if (father)
		father->lchild = child;
   if (child)
   	child->father = father;
}

t_mem_ctrl*	getInOrderPredecessor(t_mem_ctrl* toReplace, t_mem_ctrl* node)
{
	t_mem_ctrl* toReturn;

	toReturn = node;
	if (node == toReplace->lchild && !node->rchild)
	{
		FRClinkNodes(node, node->father->rchild);
		linkNodes(node->father->father, node);
	}
	else
	{
		if (node->rchild)
		{
			toReturn = getInOrderPredecessor(toReplace, node->rchild);
			node->height = maxHeight(node->lchild, node->rchild) + 1;
			checkBalance(node);
			return toReturn;
		}
		if (node->lchild)
		{
			linkNodes(node->father, node->lchild);
		}
		else
			node->father->rchild = NULL;
	}
	return toReturn;
}

t_mem_ctrl*	getInOrderSuccessor(t_mem_ctrl* toReplace, t_mem_ctrl* node)
{
	t_mem_ctrl* toReturn;

	toReturn = node;
	if (node == toReplace->rchild && !node->lchild)
	{
		FLClinkNodes(node, node->father->lchild);
		linkNodes(node->father->father, node);
	}
	else
	{
		if (node->lchild)
		{
			toReturn = getInOrderSuccessor(toReplace, node->lchild);
			node->height = maxHeight(node->lchild, node->rchild) + 1;
			checkBalance(node);
			return toReturn;
		}
		if (node->rchild)
			linkNodes(node->father, node->rchild);
		else
			node->father->lchild = NULL;
	}
	return toReturn;
}

int getHeight(t_mem_ctrl* node)
{
	return node ? node->height : 0;
}