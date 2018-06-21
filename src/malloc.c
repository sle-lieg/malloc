#include "malloc.h"

void*	malloc(size_t size)
{
	ft_printf("MALLOC(%lu)", size);
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
	// printTree2(pges_ctrl.root);
	assert(pges_ctrl.fst_tiny->prev == NULL);

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
	if (pges_ctrl.ret->size - size >= TINY_MAX)
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
