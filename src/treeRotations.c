#include "malloc.h"

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
   // linkNodes(node, tmp->lchild);
   // linkNodes(tmp, node->father);
   // linkNodes(tmp, node);
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

   // linkNodes(node, tmp->rchild);
   // linkNodes(tmp, node->father);
   // linkNodes(tmp, node);
}