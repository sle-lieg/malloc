/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 22:59:21 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/28 22:59:42 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*reallocf(void *ptr, size_t size)
{
	t_mem_ctrl *to_realloc;

	to_realloc = NULL;
	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (malloc(16));
	}
	pthread_mutex_lock(&mutex_alloc);
	to_realloc = find_mem_ctrl(pges_ctrl.root, ptr);
	pthread_mutex_unlock(&mutex_alloc);
	if (to_realloc)
	{
		if (to_realloc->size >= size)
			return (to_realloc->addr);
		if ((malloc(size)))
			ft_memmove(pges_ctrl.ret->addr, ptr, to_realloc->size);
		free(ptr);
		return (pges_ctrl.ret->addr);
	}
	return (NULL);
}
