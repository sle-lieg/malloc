#include "malloc.h"

void	linkNodes(t_mem_ctrl* father, t_mem_ctrl* child)
{
	if (father && child && child->allocatedSize <= father->allocatedSize)
	{
		ft_printf(" LINK lchild");
		father->lchild = child;
	}
	else if (father)
	{
		ft_printf(" LINK rchild");
		
		father->rchild = child;
	}
	if (child)
	{
		ft_printf(" LINK lfath");
   	child->father = father;
	}
}

void	swapNodes(t_mem_ctrl* predecessor, t_mem_ctrl* node)
{
	if (predecessor->lchild)
		linkNodes(predecessor->father, predecessor->lchild);
	if (predecessor->rchild)
		linkNodes(predecessor->father, predecessor->rchild);
	predecessor->lchild = node->lchild;
	predecessor->rchild = node->rchild;
	predecessor->father = node->father;
	node->lchild->father = predecessor;
	node->rchild->father = predecessor;
	if (node->father && node->allocatedSize <= node->father->allocatedSize)
		node->father->lchild = predecessor;
	else if (node->father)
		node->father->rchild = predecessor;
}

void  replaceIfRoot(t_mem_ctrl* node)
{
   if (pgePointers.rootTiny == node)
      pgePointers.rootTiny = node->father;
   if (pgePointers.rootSmall == node)
      pgePointers.rootSmall = node->father;
   if (pgePointers.rootLarge == node)
      pgePointers.rootLarge = node->father;
}