#include "malloc.h"

void  rotateLeft(t_mem_ctrl* node)
{
   t_mem_ctrl* tmp;

   tmp = node->rchild;

	node->rchild = tmp->lchild;
	tmp->lchild = node;

	if (node->father)
		node->father->rchild = tmp;
	tmp->father = node->father;	
	node->father = tmp;
   // linkNodes(node, tmp->lchild);
   // linkNodes(tmp, node->father);
   // linkNodes(tmp, node);
}

void  rotateRight(t_mem_ctrl* node)
{
   t_mem_ctrl* tmp;

   tmp = node->lchild;

	node->lchild = tmp->rchild;
	tmp->rchild = node;

	if (node->father)
		node->father->lchild = tmp;
	tmp->father = node->father;	
	node->father = tmp;

   // linkNodes(node, tmp->rchild);
   // linkNodes(tmp, node->father);
   // linkNodes(tmp, node);
}