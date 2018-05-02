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
