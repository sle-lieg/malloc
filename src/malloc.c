#include "malloc.h"

void*	ft_malloc(size_t size)
{
	pgePointers.toReturn = NULL;
	pgePointers.pageSize = getpagesize();
	pgePointers.requiredSize = size;
	size = (size % MEM_ALIGN) ? ((size >> MEM_ALIGN_SHIFT) << MEM_ALIGN_SHIFT) + MEM_ALIGN : size;
	if (size <= TINY_MAX)
		handleTiny(size);
	// else if (size < SMALL_MAX)
	// 	handleSmall(size);
	// else
	// 	handleLarge(size);
	if (pgePointers.errors)
		return NULL;
	return pgePointers.toReturn->data;
}

void	handleTiny(size_t size)
{
	if (!pgePointers.firstT)
		if (!(pgePointers.firstT = getNewPage(NULL, size)))
			return;
	findFreeBlock(pgePointers.firstT, size);
}

// void	handleSmall(size_t size)
// {
// 	if (!pgePointers.firstS)
// 		if (!(pgePointers.firstS = getNewPage(NULL, size)))
// 			return;
// 	findFreeBlock(pgePointers.firstS, size);
// }

// void	handleLarge(size_t size)
// {
// 	if (!pgePointers.firstL)
// 		if (!(pgePointers.firstL = getNewPage(NULL, size)))
// 			return;
// 	findFreeBlock(pgePointers.firstL, size);
// }

void	show_alloc_mem()
{
	t_datas* tmp;

	tmp = pgePointers.firstT;
	if (tmp)
		ft_printf("TINY : %p\n", tmp);	
	while (tmp)
	{
		ft_printf("%#5X - %#5X : %d octets\n", tmp->data, tmp->next, tmp->size);
		tmp = tmp->next;
	}
}