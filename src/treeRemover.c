#include "malloc.h"

void	removeNode(t_mem_ctrl* node)
{
	ft_printf("RemoveNode(%p)\n", node);	
	if (!node->lchild && !node->rchild)
		removeLeaf(node);
	else if (node->lchild && node->rchild)
		removeParentOfChildren(node);
	else
		removeParentOfOrphan(node);
	node->free = FALSE;
	node->father = NULL;
	node->lchild = NULL;
	node->rchild = NULL;
}

void	removeLeaf(t_mem_ctrl* node)
{
	ft_printf("Remove leaf\n");	
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = NULL;
	else if (node == node->father->lchild)
		node->father->lchild = NULL;
	else if (node == node->father->rchild)
		node->father->rchild = NULL;
	// else if (node->allocatedSize <= node->father->allocatedSize)
	// 	node->father->lchild = NULL;
	// else
	// 	node->father->rchild = NULL;
}

void	removeParentOfChildren(t_mem_ctrl* node)
{
	ft_printf("Remove childrens\n");
	t_mem_ctrl* tmp;

	if (node->lchild->height >= node->rchild->height)
	{
		tmp = getInOrderPredecessor(node->lchild);
		if (node->lchild != tmp)
		{
			swapNodes(tmp, node);
			// ft_printf("After2: N=%p F=%p LC=%p RC=%p\n", node, node->father, node->lchild, node->rchild);
		}
	}
	else
	{
		tmp = getInOrderSuccessor(node->rchild);
		if (node->rchild != tmp)
			swapNodes(tmp, node);		
	}
	if (node == pgePointers.rootTiny)
	{
		pgePointers.rootTiny = tmp;
	}
}

void	removeParentOfOrphan(t_mem_ctrl* node)
{
	ft_printf("Remove orphan\n");
	// printTree2(pgePointers.rootTiny);
	if (node->lchild)
		linkNodes(node->father, node->lchild);
	else
		linkNodes(node->father, node->rchild);
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = node->lchild ? node->lchild : node->rchild;
		// printTree2(pgePointers.rootTiny);		
}
