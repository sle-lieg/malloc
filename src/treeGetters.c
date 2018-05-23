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

t_mem_ctrl*	getInOrderPredecessor(t_mem_ctrl* node)
{
	if (!node->rchild)
	{
		FRClinkNodes(node, node->father->rchild);
		linkNodes(node->father->father, node);
	}
	else
	{
		// ft_printf("Predecessor 2\n");		
		while (node->rchild)
		{
			if (!node->lchild || (node->lchild && node->lchild->height != node->height - 1))
				node->height--;
			node = node->rchild;
		}
		if (node->lchild)
			linkNodes(node->father, node->lchild);
		else
			node->father->rchild = NULL;
	}
	return node;
}

t_mem_ctrl*	getInOrderSuccessor(t_mem_ctrl* node)
{
	if (!node->lchild)
	{
		FLClinkNodes(node, node->father->lchild);
		linkNodes(node->father->father, node);
	}
	else
	{
		while (node->lchild)
		{
			if (!node->rchild || (node->rchild && node->rchild->height != node->height - 1))
				node->height--;
			node = node->lchild;
		}
		// printTree2(pgePointers.rootTiny);	
		
		if (node->rchild)
			linkNodes(node->father, node->rchild);
		else
			node->father->lchild = NULL;
	}
	return node;
}

int getHeight(t_mem_ctrl* node)
{
	return node ? node->height : 0;
}