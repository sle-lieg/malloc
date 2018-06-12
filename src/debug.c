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

	tmp = pgePointers.firstTinyCtrl;
	if (tmp)
		ft_printf("TINY\n");
	while (tmp)
	{
		ft_printf("Header: %#5X: %#5X - %#5X :\
		memAlloc: %d. memRequired: %d octets\n",\
		tmp,\
		tmp->pageAddr,\
		tmp->pageAddr + tmp->allocatedSize,\
		tmp->allocatedSize,\
		tmp->requiredSize);

		tmp = tmp->next;
	}
	ft_printf("LAST: %#5X: %#5X - %#5X : %d octets\n", pgePointers.lastTinyCtrl, pgePointers.lastTinyCtrl->pageAddr, pgePointers.lastTinyCtrl->pageAddr + pgePointers.lastTinyCtrl->allocatedSize, pgePointers.lastTinyCtrl->allocatedSize);
}

void	printTree2(t_mem_ctrl* root)
{
	if (!root)
		return;
	ft_printf("---	N[%d][%d]{%lu}: addr=%p | page=%p | father:%p | lchild=%p | rchild=%p \n", checkDepth(root), root->height, root->allocatedSize, root, root->pageAddr, root->father, root->lchild, root->rchild);
	printTree2(root->lchild);
	printTree2(root->rchild);
}

void	printTree(t_mem_ctrl* root)
{
	int i;

	ft_printf("ALL FREE NODES:\n	");
	if (!root)
		return;
	// checkHeight(root);
	i = 1;
	while (i <= root->height)
	{
		printLevels(root, i);
		i++;
		ft_printf("\n");
	}
	ft_printf("\n");
}

void 	printLevels(t_mem_ctrl* node, int i)
{
	// int j;

	if (!node)
		return;
	// j = 0;
	if (i == checkDepth(node))
	{
		ft_printf("	NODE[%d]: pageAddr=%p | addr=%p | lchild=%p | rchild=%p |", i, node->pageAddr, node, node->lchild, node->rchild);
		return;
	}
	printLevels(node->lchild, i);
	printLevels(node->rchild, i);
}

void	printAll()
{
	t_mem_ctrl* tmp;
	int i;

	i = 0;
	ft_printf("ALL ALLOCATIONS:\n	");
	tmp = pgePointers.firstTinyCtrl;
	while (tmp)
	{
		if (++i % 3 == 0)
			ft_printf("\n	");	
		ft_printf("| [%d]{%lu}MC%d=%p, PA=%p |->",tmp->height, tmp->allocatedSize, tmp->free, tmp, tmp->pageAddr);
		if (!tmp->next)
			ft_printf("HEAP SIZE LEFT= %lu", tmp->allocatedSize);
		tmp = tmp->next;
	}
	ft_printf("\n");
	ft_printf("*** Last Tiny: %p, lchild: %p, rchild: %p, fath: %p\n", pgePointers.lastTinyCtrl, pgePointers.lastTinyCtrl->lchild, pgePointers.lastTinyCtrl->rchild, pgePointers.lastTinyCtrl->father);
	ft_printf("\n");	
}

void 	printLosts()
{
	t_mem_ctrl* tmp;
	ft_printf("LOSTS: ");

	tmp = pgePointers.lost_mem_ctrl;
	while (tmp)
	{
		ft_printf("%p -> ",tmp);
		// ft_printf("| [%d]{%lu}MC%d=%p, PA=%p |->",tmp->height, tmp->allocatedSize, tmp->free, tmp, tmp->pageAddr);
		tmp = tmp->next;		
	}
	ft_printf("\n");
	
}

// void 	printLevels(t_mem_ctrl* node, int i)
// {
// 	int j;

// 	if (!node)
// 		return;
// 	j = 0;
// 	if (i == checkDepth(node))
// 	{
// 		if (node->father && !node->father->lchild)
// 			// while (j++ < maxHeight(node->lchild, node->rchild) + 1)
// 			while (j++ < node->height + 1)
// 				ft_printf("    ");
// 		j = 0;			
// 		// while (j++ < maxHeight(node->lchild, node->rchild) + 1)
// 		while (j++ < node->height + 1)
// 			ft_printf("    ");
// 		ft_printf("%d", node->allocatedSize);
// 		// while (j--)
// 		// 	ft_printf("    ");
// 		return;
// 	}
// 	printLevels(node->lchild, i);
// 	printLevels(node->rchild, i);
// }
