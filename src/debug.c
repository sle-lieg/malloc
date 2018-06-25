#include "malloc.h"

int checkDepth(t_mem_ctrl* node)
{
	if (node->father)
		return (checkDepth(node->father) + 1);
	return 1;
}

void	show_alloc_mem()
{
	t_mem_ctrl* tmp;
	t_mem_ctrl* tmp_prev;

	tmp = pges_ctrl.fst_tiny;
	if (tmp)
		ft_printf("TINY\n");
	while (tmp)
	{
		if (tmp->free)
			ft_printf("[F]");
		else
			ft_printf("[N]");
		ft_printf("{page: %d}Hdr: %p - addr: %p - size: %d.\n",\
		tmp->pge_id, tmp, tmp->addr, tmp->size);
		tmp_prev = tmp;
		tmp = tmp->next;
		// if (tmp)
			// assert(tmp->prev == tmp_prev);
	}
	// ft_printf("LAST: %#5X: %#5X - %#5X : %d octets\n", pges_ctrl.lst_tiny, pges_ctrl.lst_tiny->addr, pges_ctrl.lst_tiny->addr + pges_ctrl.lst_tiny->size, pges_ctrl.lst_tiny->size);
	
	ft_printf("***********************************************\n");
	tmp = pges_ctrl.fst_small;
	if (tmp)
		ft_printf("SMALL\n");
	while (tmp)
	{
		if (tmp->free)
			ft_printf("[F]");
		else
			ft_printf("[N]");
		ft_printf("{page: %d}Hdr: %p - addr: %p - size: %d.\n",\
		tmp->pge_id, tmp, tmp->addr, tmp->size);
		tmp = tmp->next;
	}
	// ft_printf("LAST: %#5X: %#5X - %#5X : %d octets\n", pges_ctrl.lastSmallCtrl, pges_ctrl.lastSmallCtrl->addr, pges_ctrl.lastSmallCtrl->addr + pges_ctrl.lastSmallCtrl->size, pges_ctrl.lastSmallCtrl->size);
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
		ft_printf("Ad->%p ", root->lchild->addr);
	ft_printf("| rchild: H->%p ", root->rchild);
	if (root->rchild)
		ft_printf("Ad->%p ", root->rchild->addr);
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

// void	printTree(t_mem_ctrl* root)
// {
// 	int i;

// 	ft_printf("ALL FREE NODES:\n	");
// 	if (!root)
// 		return;
// 	// checkHeight(root);
// 	i = 1;
// 	while (i <= root->height)
// 	{
// 		printLevels(root, i);
// 		i++;
// 		ft_printf("\n");
// 	}
// 	ft_printf("\n");
// }

// void 	printLevels(t_mem_ctrl* node, int i)
// {
// 	// int j;

// 	if (!node)
// 		return;
// 	// j = 0;
// 	if (i == checkDepth(node))
// 	{
// 		ft_printf("	NODE[%d]: addr=%p | addr=%p | lchild=%p | rchild=%p |", i, node->addr, node, node->lchild, node->rchild);
// 		return;
// 	}
// 	printLevels(node->lchild, i);
// 	printLevels(node->rchild, i);
// }

// void	printAll()
// {
// 	t_mem_ctrl* tmp;
// 	int i;

// 	i = 0;
// 	// ft_printf("ALL ALLOCATIONS: count = %zu\n	", pges_ctrl.count);
// 	tmp = pges_ctrl.fst_tiny;
// 	while (tmp)
// 	{
// 		if (++i % 3 == 0)
// 			ft_printf("\n	");
// 		ft_printf("| [%d]{%lu}MC%d=%p, PA=%p |->",tmp->pge_id, tmp->size, tmp->free, tmp, tmp->addr);
// 		if (!tmp->next)
// 			ft_printf("HEAP SIZE LEFT= %lu", tmp->size);
// 		tmp = tmp->next;
// 	}
// 	ft_printf("\n");
// 	ft_printf("*** Last Tiny: %p, lchild: %p, rchild: %p, fath: %p\n", pges_ctrl.lst_tiny, pges_ctrl.lst_tiny->lchild, pges_ctrl.lst_tiny->rchild, pges_ctrl.lst_tiny->father);
// 	ft_printf("\n");	
// }

// void 	printLosts()
// {
// 	t_mem_ctrl* tmp;
// 	ft_printf("LOSTS: ");

// 	tmp = pges_ctrl.lost_headers;
// 	while (tmp)
// 	{
// 		ft_printf("%p -> ",tmp);
// 		// ft_printf("| [%d]{%lu}MC%d=%p, PA=%p |->",tmp->height, tmp->size, tmp->free, tmp, tmp->addr);
// 		tmp = tmp->next;		
// 	}
// 	ft_printf("\n");
	
// }

// void	checkFree()
// {
// 	t_mem_ctrl* tmp;

// 	tmp = pges_ctrl.fst_tiny;
// 	while (tmp->next)
// 	{
// 		if (tmp->free && tmp->next->free && tmp->pge_id == tmp->next->pge_id)
// 		{
// 			ft_printf("FREEEEEEEEEEEE\n");	
// 			printAll();
// 			printTree2(pges_ctrl.root_headers);
// 		}
// 		tmp = tmp->next;
// 	}
// }

// void	checkGoodHeight(t_mem_ctrl* node)
// {
// 	if (node)
// 	{
// 		if (node->lchild && node->rchild)
// 		{
// 			// if (node->height != node->lchild->height + 1 && node->height != node->rchild->height + 1)
// 			if (node->height != maxHeight(node->lchild, node->rchild) + 1)
// 			{
// 				ft_printf("TREE ERROR !!!\n");			
// 				exit(0);
// 			}
// 		}
// 		else if (node->lchild)
// 		{
// 			if (node->height != node->lchild->height + 1)
// 			{
// 				ft_printf("TREE ERROR !!!\n");
// 				exit(0);
// 			}
// 		}
// 		else if (node->rchild)
// 		{
// 			if (node->height != node->rchild->height + 1)
// 			{
// 				ft_printf("TREE ERROR !!!\n");			
// 				exit(0);
// 			}
// 		}
// 		checkGoodHeight(node->lchild);
// 		checkGoodHeight(node->rchild);
// 	}
// }
