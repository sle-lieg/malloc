#include "malloc.h"

void*	getNewPage(size_t size)
{
	void* tmp;

	tmp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == MAP_FAILED)
	{
		pgePointers.errors |= MMAP_BAD_ALLOC;
		return NULL;
	}
	return tmp;
}

void	createMemCtrl(t_mem_ctrl* newNodeAddr, void* pageAddress, size_t size)
{

}

/**
 **					findFreeBlock
 **	recursive to find a free block big enough, from root block.
 **	the tree contains only free blocks, sorted by size.
 **	when a block is found, call splitBlock(). if none found, it means there is
 **	not enough space left on the page, so create a new t_memCtrl, and store
 ** in its ->pageAddr a new fresh page. 
 **/
void	findFreeBlock(t_mem_ctrl* block, size_t size)
{
	if (block->lnode && block->lnode->allocatedSize > size)
		findFreeBlock(block->lnode, size);
	else if (block->rnode && block->rnode->allocatedSize > size)
	
}

// void initBlock(t_mem_ctrl* newBlock, t_mem_ctrl* lastBlock, size_t size)
// {
// 	newBlock->prev = lastBlock;
// 	newBlock->next = lastBlock ? lastBlock->next : NULL;
// 	newBlock->size = size;
// 	newBlock->free = 1;
// 	if (lastBlock)
// 		lastBlock->next = newBlock;
// 	else
// 		newBlock->size = pgePointers.pageSize - DATAS_CTRL_SIZE;
// }

// void	findFreeBlock(t_mem_ctrl* block, size_t size)
// {
// 	while (block)
// 	{
// 		if (block->free && (block->size >= size))
// 		{
// 			splitBlock(block, size);
// 			return;
// 		}
// 		if (!block->next)
// 			getNewPage(block, size);
// 		else
// 			block = block->next;
// 	}
// }

/*
	- if there is { size + (block_size) } available:
		create a block_ctrl at block->data + size;
		link block to new block and new block to block next
	- else
		just return the block in state
*/
void	splitBlock(t_mem_ctrl* block, size_t size)
{
	int	newBlockSize;

	newBlockSize = block->size - size - DATAS_CTRL_SIZE;
	pgePointers.toReturn = block;
	block->free = 0;
	if (block->size < (size + DATAS_CTRL_SIZE))
		return;
	block->size = size;
	initBlock((t_mem_ctrl*)block->data + size, block, newBlockSize);
}