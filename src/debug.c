/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:16:45 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/06/29 15:18:28 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_mem(char *mem)
{
	char *str;

	str = ft_itoa_base((uint64_t)mem, 16);
	ft_putstr("0x");
	if (str)
		ft_putstr(str);
	else
		ft_putstr("0x0");
}

static void	show_mem(t_mem_ctrl *tmp)
{
	if (!tmp)
		return ;
	while (tmp)
	{
		print_mem(tmp->addr);
		ft_putstr(" - ");
		print_mem(tmp->addr + tmp->size);
		ft_putstr(" : ");
		ft_putnbr(tmp->size);
		tmp = tmp->next;
		ft_putstr(" octets\n");
	}
}

void		show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex_alloc);
	if (g_pges_ctrl.fst_tiny)
	{
		ft_putstr("TINY: ");
		print_mem(g_pges_ctrl.fst_tiny->addr);
		ft_putstr("\n");
	}
	show_mem(g_pges_ctrl.fst_tiny);
	if (g_pges_ctrl.fst_small)
	{
		ft_putstr("SMALL: ");
		print_mem(g_pges_ctrl.fst_small->addr);
		ft_putstr("\n");
	}
	show_mem(g_pges_ctrl.fst_small);
	if (g_pges_ctrl.fst_large)
	{
		ft_putstr("LARGE: ");
		print_mem(g_pges_ctrl.fst_large->addr);
		ft_putstr("\n");
	}
	show_mem(g_pges_ctrl.fst_large);
	pthread_mutex_unlock(&g_mutex_alloc);
}
