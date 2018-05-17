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
		// ft_printf("Predecessor 1\n");
		// printTree2(pgePointers.rootTiny);	
		// ft_printf("GIP Before: N=%p F=%p LC=%p RC=%p\n", node, node->father, node->lchild, node->rchild);
		// linkNodes(node, node->father->rchild);
		// linkNodes(node->father->father, node);
		FRClinkNodes(node, node->father->rchild);
		linkNodes(node->father->father, node);
		// printTree(pgePointers.rootTiny);	
		// ft_printf("GIP After: N=%p F=%p LC=%p RC=%p\n", node, node->father, node->lchild, node->rchild);		
	}
	else
	{
		// ft_printf("Predecessor 2\n");		
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
		// ft_printf("Successor 1\n");		
		// ft_printf("GIS Before: N=%p F=%p LC=%p RC=%p\n", node, node->father, node->lchild, node->rchild);
		
		// linkNodes(node, node->father->lchild);
		// linkNodes(node->father->father, node);
		FLClinkNodes(node, node->father->lchild);
		linkNodes(node->father->father, node);
		// ft_printf("GIS After: N=%p F=%p LC=%p RC=%p\n", node, node->father, node->lchild, node->rchild);		
	}
	else
	{
		// ft_printf("Successor 2\n");	
		// printAll();	
		while (node->lchild)
		{
			node = node->lchild;
		}
		// printTree2(pgePointers.rootTiny);	
		
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