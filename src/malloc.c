#include "malloc.h"

void*	malloc(size_t size)
{
	if (!checkLimit(size))
		return NULL;
	pges_ctrl.tiny_zone = (((TINY_MAX * 100) >> 12) << 12) + getpagesize();
	pges_ctrl.small_zone = (((SMALL_MAX * 100) >> 12) << 12) + getpagesize();
	pges_ctrl.ret = NULL;
	size = align_memory(size);
	assert(pges_ctrl.tiny_zone == 16384);
	if (!pges_ctrl.header_pge || pges_ctrl.header_pge == pges_ctrl.header_pge_limit)
		if (!(extend_header_pge()))
			return NULL;
	if (size <= TINY_MAX)
		handle_tiny(size);
	else if (size <= SMALL_MAX)
		handle_small(size);
	// else
	// 	handleLarge(size);
	show_alloc_mem();
	printTree2(pges_ctrl.root);
	if (pges_ctrl.errors)
		return NULL;
	return pges_ctrl.ret->addr;
}

void	handle_tiny(size_t size)
{
	if (!pges_ctrl.fst_tiny)
		if (!init_tiny(size))
			return;
	find_free_block(pges_ctrl.free_tiny, size);
	if (!pges_ctrl.ret)
	{
		if (!(extend_heap(pges_ctrl.lst_tiny)))
			return;
		pges_ctrl.lst_tiny = pges_ctrl.ret;
	}
	if (pges_ctrl.ret->size - size >= 16)
	{
		split_memory(size);
		add_to_free(&pges_ctrl.free_tiny, pges_ctrl.ret->next);
		if (pges_ctrl.ret == pges_ctrl.lst_tiny)
			pges_ctrl.lst_tiny = pges_ctrl.ret->next;
	}
}

void	handle_small(size_t size)
{
	if (!pges_ctrl.fst_small)
		if (!init_small(size))
			return;
	find_free_block(pges_ctrl.free_small, size);
	if (!pges_ctrl.ret)
	{
		if (!(extend_heap(pges_ctrl.lst_small)))
			return;
		pges_ctrl.lst_small = pges_ctrl.ret;
	}
	if (pges_ctrl.ret->size - size >= 16)
	{
		split_memory(size);
		add_to_free(&pges_ctrl.free_small, pges_ctrl.ret->next);
		if (pges_ctrl.ret == pges_ctrl.lst_small)
			pges_ctrl.lst_small = pges_ctrl.ret->next;
	}
}

void	handle_large(size_t size)
{
	t_mem_ctrl* new_large;

	if (!(new_large = create_new_page(size)))
		return;
	add_node(new_large);
}

t_mem_ctrl*	split_memory(size_t size)
{
	t_mem_ctrl* new_header;

	// if (!(new_header = pop_lost_header()))
		new_header = pges_ctrl.header_pge++;	

	new_header->addr = pges_ctrl.ret->addr + size;
	new_header->size = pges_ctrl.ret->size - size;
	new_header->prev = pges_ctrl.ret;
	new_header->next = pges_ctrl.ret->next;
	pges_ctrl.ret->size = size;
	pges_ctrl.ret->next = new_header;
	if (pges_ctrl.ret->next)
		pges_ctrl.ret->next->prev = new_header;
	add_node(new_header);
	return NULL;
}

void	find_free_block(t_mem_ctrl* block, size_t size)
{
	while (block)
	{
		if (block->size >= size)
		{
			pges_ctrl.ret = block;
			remove_from_free(block);
			break;
		}
		block = block->next_free;
	}
}

void	add_to_free(t_mem_ctrl** free_head, t_mem_ctrl* new_header)
{
	new_header->next_free = *free_head;
	*free_head = new_header;
	new_header->free = TRUE;
}

void	remove_from_free(t_mem_ctrl* block)
{
	t_mem_ctrl* tmp;

	tmp = NULL;
	if (pges_ctrl.free_tiny == block)
		pges_ctrl.free_tiny = block->next;
	else if (pges_ctrl.free_small == block)
		pges_ctrl.free_small = block->next;
	else
	{
		while (tmp->next)
		{
			if (tmp->next == block)
			{
				tmp->next = block->next;
				break;
			}
			tmp = tmp->next;
		}
	}
	block->free = FALSE;
	block->next_free = NULL;
}

int	extend_heap(t_mem_ctrl* last_mctrl)
{
	// if (!(pges_ctrl.ret = pop_lost_header()))
		pges_ctrl.ret = pges_ctrl.header_pge++;
	last_mctrl->next = pges_ctrl.ret;
	pges_ctrl.ret->prev = last_mctrl;
	if (!(pges_ctrl.ret->addr = create_new_page(pges_ctrl.tiny_zone)))
		return (0);
	pges_ctrl.ret->size = pges_ctrl.tiny_zone;
	pges_ctrl.ret->free = TRUE;
	pges_ctrl.ret->pge_id = ++pges_ctrl.pages_id;
	return (1);
}

// ******************************************

	// // ft_printf("TINY\n");
	// if (!pges_ctrl.fst_tiny)
	// 	if (!initRootTiny(size))
	// 		return;
	// findFreeBlock(pges_ctrl.rootTiny, size);

	// if (!pges_ctrl.toReturn) // not enough place on the heap, need to allocate a new page.
	// {
	// 	if (!(pges_ctrl.toReturn = createNewTinyMemCtrl(getLastLink(pges_ctrl.fst_tiny))))
	// 		return;
	// 	pges_ctrl.toReturn->free = FALSE;
	// 	getNewPage(pges_ctrl.toReturn, size);
	// 	if (pges_ctrl.errors)
	// 		return;
	// }
	// else
	// 	removeNode(pges_ctrl.toReturn);
	// if (size + 32 <= pges_ctrl.toReturn->allocatedSize)
	// 	addNode(&pges_ctrl.rootTiny, splitMemory(size));
// }

// void	handleSmall(size_t size)
// {
// 	ft_printf("SMALL\n");	
// 	if (!pges_ctrl.firstSmallCtrl)
// 		if (!initRootSmall(size))
// 			return;
// 	findFreeBlock(pges_ctrl.rootSmall, size);

// 	if (!pges_ctrl.toReturn) // not enough place on the heap, need to allocate a new page.
// 	{
// 		if (!(pges_ctrl.toReturn = createNewSmallMemCtrl(getLastLink(pges_ctrl.firstSmallCtrl))))
// 			return;
// 		pges_ctrl.toReturn->free = FALSE;
// 		getNewPage(pges_ctrl.toReturn, size);
// 		if (pges_ctrl.errors)
// 			return;
// 	}
// 	else
// 		removeNode(pges_ctrl.toReturn);
// 	if (size + 256 <= pges_ctrl.toReturn->allocatedSize)
// 		addNode(&pges_ctrl.rootSmall, splitMemory(size));
// }

// void	handleLarge(size_t size)
// {
// 	ft_printf("LARGE\n");
// 	if (!pges_ctrl.firstLargeCtrl)
// 		if (!initRootLarge(size))
// 			return;
// 	// findFreeBlock(pges_ctrl.rootLarge, size);

// 	// if (!pges_ctrl.toReturn) // not enough place on the heap, need to allocate a new page.
// 	// {
// 		if (!(pges_ctrl.toReturn = createNewLargeMemCtrl(getLastLink(pges_ctrl.firstLargeCtrl))))
// 			return;
// 		pges_ctrl.toReturn->free = FALSE;
// 		getNewPage(pges_ctrl.toReturn, size);
// 		if (pges_ctrl.errors)
// 			return;
// 	// }
// 	// else
// 	// 	removeNode(pges_ctrl.toReturn);
// 	// if (size + 32 <= pges_ctrl.toReturn->allocatedSize)
// 	// 	addNode(&pges_ctrl.rootSmall, splitMemory(size));
// }

int	checkLimit(size_t size)
{
	struct rlimit limit;

	getrlimit(RLIMIT_DATA, &limit);
	if (size > limit.rlim_max)
		return 0;
	return 1;
}

size_t align_memory(size_t size)
{
	if (!size)
		size = MEM_ALIGN;
	else if (size % MEM_ALIGN)
		size = ((size >> MEM_ALIGN_SHIFT) << MEM_ALIGN_SHIFT) + MEM_ALIGN;
	assert(size % MEM_ALIGN == 0);
	return size;
}
