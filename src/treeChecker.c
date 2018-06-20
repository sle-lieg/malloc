#include "malloc.h"

int	check_balance(t_mem_ctrl* node)
{
	// if (!pges_ctrl.count)
	// 	ft_printf("CheckBalance\n");
   int factor;

   factor = get_height(node->lchild) - get_height(node->rchild);
	if (factor > 1)
	{
		if (check_balance(node->lchild) >= 0)
			rotateRight(node);
		else
		{
			rotateLeft(node->lchild);
			rotateRight(node);
		}
	}
	else if (factor < -1)
	{
		if (check_balance(node->rchild) <= 0)
			rotateLeft(node);
		else
		{
			rotateRight(node->rchild);
			rotateLeft(node);
		}
	}
	if (factor < -1 || factor > 1)
		replaceIfRoot(node, node->father);
	return factor;
}

int	max_height(t_mem_ctrl* nodeA, t_mem_ctrl* nodeB)
{
	if (!nodeA && !nodeB)
		return 0;
	if (nodeA && !nodeB)
		return nodeA->height;
	else if (!nodeA && nodeB)
		return nodeB->height;
	return nodeA->height > nodeB->height ? nodeA->height : nodeB->height;
}

void	check_height(t_mem_ctrl* node)
{
	// ft_printf("CheckHeight\n");
	if (!node)
		return;
	check_height(node->lchild);
	check_height(node->rchild);
	node->height = max_height(node->lchild, node->rchild) + 1;
}
