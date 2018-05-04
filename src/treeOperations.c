#include "malloc.h"

void	findFreeBlock(t_mem_ctrl* node, size_t size)
{
	if (pgePointers.toReturn)
		return;
	if (node->lchild && size < node->allocatedSize)
		findFreeBlock(node->lchild, size);
	if (size <= node->allocatedSize && !pgePointers.toReturn)
		pgePointers.toReturn = node;
	else if (node->rchild && !pgePointers.toReturn)
		findFreeBlock(node->rchild, size);
}


void	removeNode(t_mem_ctrl* node)
{
	if (!node->lchild && !node->rchild)
		removeLeaf(node);
	else if (node->lchild && node->rchild)
		removeParentOfChildren(node);
	else
		removeParentOfOrphan(node);
}

void	removeLeaf(t_mem_ctrl* node)
{
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = NULL;
	else if (node->allocatedSize <= node->father->allocatedSize)
		node->father->lchild = NULL;
	else
		node->father->rchild = NULL;
}

void	removeParentOfChildren(t_mem_ctrl* node)
{
	t_mem_ctrl* tmp;

	if (getTreeHeight(node->lchild) > getTreeHeight(node->rchild))
	{
		tmp = getInOrderPredecessor(node->lchild);
		if (node->lchild != tmp)
			swapNodes(tmp, node);
	}
	else
	{
		tmp = getInOrderSuccessor(node->rchild);
		if (node->rchild != tmp)
			swapNodes(tmp, node);		
	}
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = tmp;
}

void	removeParentOfOrphan(t_mem_ctrl* node)
{
	if (node->lchild)
		linkNodes(node->father, node->lchild)
	else
		linkNodes(node->father, node->rchild)
	if (node == pgePointers.rootTiny)
		pgePointers.rootTiny = node->lchild ? node->lchild : node->rchild;
}

void	linkNodes(t_mem_ctrl* father, t_mem_ctrl* child)
{
	if (father && father->allocatedSize < child->allocatedSize)
		father->rchild = child;
	else if (father)
		father->lchild = child;
	child->father = father;
}

void	swapNodes(t_mem_ctrl* predecessor, t_mem_ctrl* node)
{
	if (predecessor->lchild)
		linkNodes(predecessor->father, predecessor->lchild);
	if (predecessor->rchild)
		linkNodes(predecessor->father, predecessor->rchild);
	predecessor->lchild = node->lchild;
	predecessor->rchild = node->rchild;
	predecessor->father = node->father;
	node->lchild->father = predecessor;
	node->rchild->father = predecessor;
	if (node->father && node->allocatedSize <= node->father->allocatedSize)
		node->father->lchild = predecessor;
	else if (node->father)
		node->father->rchild = predecessor;
}

t_mem_ctrl*	getInorderPredecessor(t_mem_ctrl* node)
{
	if (!node->rchild)
	{
		linkNodes(node->father->father, node);
		linkNodes(node, node->father->rchild);
	}
	else
	{
		while (node->rchild)
			node = node->rchild;
		if (node->lchild)
			linkNodes(node->father, node->lchild);
		node->father->rchild = NULL;
	}
	return node;
}

void	addNode(t_mem_ctrl** root, t_mem_ctrl* newNode)
{
	if (!*root)
		*root = newNode;
	else
		recursiveAdd(*root, newNode);
}

void	recursiveAdd(t_mem_ctrl* node, t_mem_ctrl* newNode)
{
	if (newNode->allocatedSize <= node->allocatedSize)
	{
		if (node->lchild)
			recursiveAdd(node->lchild, newNode);
		else
			linkNodes(node, newNode);
	}
	else
	{
		if (node->rchild)
			recursiveAdd(node->rchild, newNode);
		else
			linkNodes(node, newNode);
	}
}