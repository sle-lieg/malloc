#include "malloc.h"

void	add_links(t_mem_ctrl* father, t_mem_ctrl* child)
{
	// assert(father != NULL);
	// assert(child != NULL);
	// if (father && child && child->addr <= father->addr)
	if (child->addr <= father->addr)
	{
		father->lchild = child;
	}
	else if (father)
	{
		father->rchild = child;
	}
	if (child)
	{
		child->father = father;
	}
}

int	replace_if_root(t_mem_ctrl* node, t_mem_ctrl* newRoot)
{
	if (pges_ctrl.root == node)
	{
		pges_ctrl.root = newRoot;
		return (1);
	}
	return (0);
}

int	get_height(t_mem_ctrl* node)
{
	return node ? node->height : 0;
}

void	swap_nodes(t_mem_ctrl* predecessor, t_mem_ctrl* node)
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
}

void	link_nodes(t_mem_ctrl* father, t_mem_ctrl* child)
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
