#include "malloc.h"

void	linkNodes(t_mem_ctrl* father, t_mem_ctrl* child)
{
	if (father && child && father->lchild == child->father)
	{
		// ft_printf(" LINK lchild");
		father->lchild = child;
	}
	else if (father)
	{
		// ft_printf(" LINK rchild");
		father->rchild = child;
	}
	if (child)
	{
		// ft_printf(" LINK lfath");
   	child->father = father;
	}
}

void  add_links(t_mem_ctrl* father, t_mem_ctrl* child)
{
	if (father && child && child->addr <= father->addr)
	{
		// ft_printf(" LINK lchild");
		father->lchild = child;
	}
	else if (father)
	{
		// ft_printf(" LINK rchild");
		father->rchild = child;
	}
	if (child)
	{
		// ft_printf(" LINK lfath");
   	child->father = father;
	}
}

void	swapNodes(t_mem_ctrl* predecessor, t_mem_ctrl* node)
{
	predecessor->lchild = node->lchild;
	predecessor->rchild = node->rchild;
	predecessor->father = node->father;
	node->lchild->father = predecessor;
	node->rchild->father = predecessor;
	if (node->father && node->father->lchild == node)
		node->father->lchild = predecessor;
	else if (node->father)
		node->father->rchild = predecessor;
	node->father = predecessor->father; //TODO: WHY ??
}

int	replaceIfRoot(t_mem_ctrl* node, t_mem_ctrl* newRoot)
{
	if (pges_ctrl.root == node)
	{
		pges_ctrl.root = newRoot;
		return (1);
	}
	return (0);
}

// int	isLastMemCtrl(t_mem_ctrl* ptr)
// {
// 	if (ptr == pges_ctrl.lastTinyCtrl || ptr == pges_ctrl.lastSmallCtrl ||
// 		ptr == pges_ctrl.lastLargeCtrl)
// 		return 1;
// 	return 0;
// }
