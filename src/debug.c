#include "malloc.h"

static void show_mem(t_mem_ctrl* tmp)
{
	if (!tmp)
		return;
	while (tmp)
	{
		if (tmp->free)
			ft_printf("[F]");
		else
			ft_printf("[N]");
		ft_printf("{%d}Header: %p [%p - %p] : %lu octets\n", tmp->pge_id, tmp, tmp->addr, tmp->addr + tmp->size, tmp->size);
		tmp = tmp->next;
	}
}

void	show_alloc_mem()
{
	if (pges_ctrl.fst_tiny)
		ft_printf("TINY : {}%5p\n", pges_ctrl.fst_tiny->addr);
	show_mem(pges_ctrl.fst_tiny);
	if (pges_ctrl.fst_small)
		ft_printf("SMALL : %5p\n", pges_ctrl.fst_small->addr);
	show_mem(pges_ctrl.fst_small);
	if (pges_ctrl.fst_large)
		ft_printf("LARGE : %5p\n", pges_ctrl.fst_large->addr);
	show_mem(pges_ctrl.fst_large);
}


static int checkDepth(t_mem_ctrl* node)
{
	if (node->father)
		return (checkDepth(node->father) + 1);
	return 1;
}

void	printTree2(t_mem_ctrl* root)
{
	if (!root)
		return;
	if (root->free)
		ft_printf("---	F");
	else
		ft_printf("---	N");
	ft_printf("[%d][%d]{%lu}: addr=%p | hdr=%p | father: H->%p ", checkDepth(root), root->height, root->size, root->addr, root, root->father);
	if (root->father)
		ft_printf("Ad->%p ", root->father->addr);
	ft_printf("| lchild: H->%p ", root->lchild);
	if (root->lchild)
	{
		ft_printf("Ad->%p ", root->lchild->addr);
		assert(root->addr > root->lchild->addr);
	}
	ft_printf("| rchild: H->%p ", root->rchild);
	if (root->rchild)
	{
		ft_printf("Ad->%p ", root->rchild->addr);
		assert(root->addr < root->rchild->addr);
	}
	ft_printf("\n");
	printTree2(root->lchild);
	printTree2(root->rchild);
}

void	print_empty()
{
	t_mem_ctrl* tmp;

	tmp = pges_ctrl.free_tiny;
	ft_printf("++ Empty TINY:\n");
	while (tmp)
	{
		ft_printf("	[%d]H:%p A:%p ", tmp->free, tmp, tmp->addr);
		// assert(tmp->free == 1);
		tmp = tmp->next_free;
	}
	ft_printf("\n");	
	tmp = pges_ctrl.free_small;
	ft_printf("++ Empty SMALL:\n");
	while (tmp)
	{
		ft_printf("	[%d]H:%p A:%p", tmp->free, tmp, tmp->addr);
		// assert(tmp->free == 1);	
		tmp = tmp->next_free;
	}
	ft_printf("\n");
}

void	print_lost()
{
	t_mem_ctrl* tmp;

	tmp = pges_ctrl.lost_mem_ctrl;
	if (tmp)
		ft_printf("LOST:\n");
	while (tmp)
	{
		ft_printf("	{%d}->%p ", tmp->free, tmp);
		// assert(tmp->free == 1);
		tmp = tmp->next;
	}
}
