#include "malloc.h"

void	add_node(t_mem_ctrl* new_node)
{
	// ft_printf("ADD NODE %p\n", new_node->addr);
	// assert(new_node->father == NULL);
	// assert(new_node->lchild == NULL);
	// assert(new_node->rchild == NULL);
	if (!pges_ctrl.root)
	{
		pges_ctrl.root = new_node;
		new_node->height = 1;
	}
	else
		recursive_add(pges_ctrl.root, new_node);
}

void	recursive_add(t_mem_ctrl* node, t_mem_ctrl* new_node)
{
	// assert(node != new_node);
	if (new_node->addr < node->addr)
	{
		if (node->lchild)
			recursive_add(node->lchild, new_node);
		else
		{
			add_links(node, new_node);
			new_node->height = 1;
		}
	}
	else
	{
		if (node->rchild)
			recursive_add(node->rchild, new_node);
		else
		{
			add_links(node, new_node);
			new_node->height = 1;
		}
	}
	check_balance(node);
	node->height = max_height(node->lchild, node->rchild) + 1;
}
