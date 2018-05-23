#include "malloc.h"

void	ft_swap(int* a, int* b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void  rotateLeft(t_mem_ctrl* node)
{
	ft_printf("Rotate left\n");
   t_mem_ctrl* tmp;

   tmp = node->rchild;

	node->rchild = tmp ? tmp->lchild : NULL;
	tmp ? tmp->lchild = node : 0;

	if (node->father)
	{
		// if (node->allocatedSize <= node->father->allocatedSize)
		// 	node->father->lchild = tmp;
		if (node == node->father->lchild)
			node->father->lchild = tmp;
		else
			node->father->rchild = tmp;		
	}
	tmp ? tmp->father = node->father : 0;	
	node->father = tmp;
	if (tmp->height < node->height)
		ft_swap(&(node->height), &(tmp->height));
}

void  rotateRight(t_mem_ctrl* node)
{
	ft_printf("Rotate right\n");
	
   t_mem_ctrl* tmp;

   tmp = node->lchild;

	node->lchild =   tmp ? tmp->rchild : NULL;
	tmp ? tmp->rchild = node : 0;

	if (node->father)
	{
		// if (node->allocatedSize <= node->father->allocatedSize)
		// 	node->father->lchild = tmp;
		if (node == node->father->lchild)
			node->father->lchild = tmp;
		else
			node->father->rchild = tmp;		
	}
		// node->father->rchild = tmp;
	tmp ? tmp->father = node->father : 0;	
	node->father = tmp;
	if (tmp->height < node->height)
		ft_swap(&(node->height), &(tmp->height));
   // linkNodes(node, tmp->rchild);
   // linkNodes(tmp, node->father);
   // linkNodes(tmp, node);
}