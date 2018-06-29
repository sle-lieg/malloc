/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:00:47 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 10:45:43 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_mem_ctrl *to_realloc;

	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (malloc(0));
	}
	pthread_mutex_lock(&g_mutex_alloc);
	to_realloc = find_mem_ctrl(g_pges_ctrl.root, ptr);
	pthread_mutex_unlock(&g_mutex_alloc);
	if (to_realloc)
	{
		if (to_realloc->size >= size)
			return (to_realloc->addr);
		if (!(malloc(size)))
			return (NULL);
		ft_memmove(g_pges_ctrl.ret->addr, ptr, to_realloc->size);
		free(ptr);
		return (g_pges_ctrl.ret->addr);
	}
	return (NULL);
}
