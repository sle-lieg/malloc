#include "malloc.h"

void	show_alloc_mem()
{
	t_mem_ctrl* tmp;

	tmp = pgePointers.firstTinyCtrl;
	if (tmp)
		ft_printf("TINY\n");
	while (tmp->next)
	{
		ft_printf("Header: %#5X: %#5X - %#5X :\
		memAlloc: %d. memRequired: %d octets\n",\
		tmp,\
		tmp->pageAddr,\
		tmp->pageAddr + tmp->requiredSize,\
		tmp->allocatedSize,\
		tmp->requiredSize);

		tmp = tmp->next;
	}
	ft_printf("LAST: %#5X: %#5X - %#5X : %d octets\n", pgePointers.lastTinyCtrl, pgePointers.lastTinyCtrl->pageAddr, pgePointers.lastTinyCtrl->pageAddr + pgePointers.lastTinyCtrl->allocatedSize, pgePointers.lastTinyCtrl->allocatedSize);
}

void	printTree(t_mem_ctrl* root)
{
	int i;

	i = 1;
	while (i < root->height)
	{
		ft_printf("TESTING");
		printLevels(root, i);
		i++;
	}
}

void 	printLevels(t_mem_ctrl* node, int i)
{
	int j;

	if (!node)
		return;
	j = 0;
	if (i == node->height)
	{
		while (j++ < i)
			ft_printf(" ");
		ft_printf("%d", node->allocatedSize);
		while (j--)
			ft_printf(" ");
	}
	printLevels(node->lchild, i);
	printLevels(node->rchild, i);
}