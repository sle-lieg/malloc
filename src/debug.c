#include "malloc.h"

void	show_alloc_mem()
{
	t_mem_ctrl* tmp;

	tmp = pgePointers.firstT;
	if (tmp)
		ft_printf("TINY : %p\n", tmp);	
	while (tmp)
	{
		ft_printf("%#5X - %#5X : %d octets\n", tmp->pageAddr, tmp->pageAddr + tmp->requiredSize, tmp->requiredSize);
		tmp = tmp->next;
	}
}