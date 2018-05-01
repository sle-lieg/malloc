#include "malloc.h"

t_datas*	getNewPage(t_datas* lastBlock, size_t size)
{
	t_datas* tmp;

	tmp = (t_datas*)mmap(lastBlock, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == MAP_FAILED)
	{
		pgePointers.errors |= MMAP_BAD_ALLOC;
		return NULL;
	}
	if (lastBlock && lastBlock->free && (lastBlock->data + lastBlock->size) == (char*)tmp)
		lastBlock->size += pgePointers.pageSize;
	else
		initBlock(tmp, lastBlock, size);
	return tmp;
}

void initBlock(t_datas* newBlock, t_datas* lastBlock, size_t size)
{
	newBlock->prev = lastBlock;
	newBlock->next = lastBlock ? lastBlock->next : NULL;
	newBlock->size = size;
	newBlock->free = 1;
	if (lastBlock)
		lastBlock->next = newBlock;
	else
		newBlock->size = pgePointers.pageSize - DATAS_CTRL_SIZE;
}

void	findFreeBlock(t_datas* block, size_t size)
{
	while (block)
	{
		if (block->free && (block->size >= size))
		{
			splitBlock(block, size);
			return;
		}
		if (!block->next)
			getNewPage(block, size);
		else
			block = block->next;
	}
}

/*
	- if there is { size + (block_size) } available:
		create a block_ctrl at block->data + size;
		link block to new block and new block to block next
	- else
		just return the block in state
*/
void	splitBlock(t_datas* block, size_t size)
{
	int	newBlockSize;

	newBlockSize = block->size - size - DATAS_CTRL_SIZE;
	pgePointers.toReturn = block;
	block->free = 0;
	if (block->size < (size + DATAS_CTRL_SIZE))
		return;
	block->size = size;
	initBlock((t_datas*)block->data + size, block, newBlockSize);
}