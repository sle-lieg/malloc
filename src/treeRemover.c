#include "malloc.h"

void	recursiveBalance(t_mem_ctrl* node)
{
	int factor;

	if (!node)
		return;
	
	// ft_printf(" Recursive Balance ");

	node->height = maxHeight(node->lchild, node->rchild) + 1;
   factor = getHeight(node->lchild) - getHeight(node->rchild);
	if (factor > 1)
	{
		if (checkBalance(node->lchild) > 0)
			rotateRight(node);
		else
		{
			rotateLeft(node->lchild);
			rotateRight(node);
		}
	}
	else if (factor < -1)
	{
		if (checkBalance(node->rchild) < 0)
			rotateLeft(node);
		else
		{
			rotateRight(node->rchild);
			rotateLeft(node);
		}
	}
   (factor < -1 || factor > 1) ? replaceIfRoot(node) : 0;
	recursiveBalance(node->father);
}

void	removeNode(t_mem_ctrl* node)
{
	// ft_printf("RemoveNode(%p)\n", node);
	if (!node->lchild && !node->rchild)
		removeLeaf(node);
	else if (node->lchild && node->rchild)
		removeParentOfChildren(node);
	else
		removeParentOfOrphan(node);
	
	recursiveBalance(node->father);

	node->free = FALSE;
	node->father = NULL;
	node->lchild = NULL;
	node->rchild = NULL;
}

void	removeLeaf(t_mem_ctrl* node)
{
	// ft_printf("Remove : leaf %p, lchild %p, rchild %p, fath %p\n", node, node->lchild, node->rchild, node->father);
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = NULL;
	else if (node == node->father->lchild)
	{
		// ft_printf("Remove left leaf\n");		
		node->father->lchild = NULL;
		node->father->height = node->father->rchild ? node->father->height : 1;
	}
	else if (node == node->father->rchild)
	{
		// ft_printf("Remove right leaf\n");
		node->father->rchild = NULL;
		node->father->height = node->father->lchild ? node->father->height : 1;		
	}
}

void	removeParentOfChildren(t_mem_ctrl* node)
{
	// ft_printf("Remove childrens\n");
	t_mem_ctrl* tmp;

	if (node->lchild->height >= node->rchild->height)
	{
		tmp = getInOrderPredecessor(node->lchild);
		if (node->lchild != tmp)
		{
			swapNodes(tmp, node);
			// ft_printf("After2: N=%p F=%p LC=%p RC=%p\n", node, node->father, node->lchild, node->rchild);
		}
		tmp->height = maxHeight(tmp->lchild, tmp->rchild) + 1;
	}
	else
	{
		tmp = getInOrderSuccessor(node->rchild);
		if (node->rchild != tmp)
		{
			swapNodes(tmp, node);		
		}
		tmp->height = maxHeight(tmp->lchild, tmp->rchild) + 1;
	}
	if (node == pgePointers.rootTiny)
	{
		pgePointers.rootTiny = tmp;
	}
}

void	removeParentOfOrphan(t_mem_ctrl* node)
{
	// ft_printf("Remove orphan\n");
	// printTree2(pgePointers.rootTiny);
	if (node->lchild)
		linkNodes(node->father, node->lchild);
	else
		linkNodes(node->father, node->rchild);
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = node->lchild ? node->lchild : node->rchild;
		// printTree2(pgePointers.rootTiny);		
}
