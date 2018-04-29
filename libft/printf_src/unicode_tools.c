/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 01:19:36 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/03/10 01:41:59 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_four_octet(t_env *e, uint32_t arg)
{
	*e->pos++ ^= (0xF0 + (arg >> 18));
	*e->pos++ ^= (0x80 + ((arg << 14) >> 26));
	*e->pos++ ^= (0x80 + ((arg << 20) >> 26));
	*e->pos++ ^= (0x80 + ((arg << 26) >> 26));
	return (4);
}

int	ft_three_octet(t_env *e, uint32_t arg)
{
	*e->pos++ ^= (0xE0 + ((arg << 14) >> 26));
	*e->pos++ ^= (0x80 + ((arg << 20) >> 26));
	*e->pos++ ^= (0x80 + ((arg << 26) >> 26));
	return (3);
}

int	ft_two_octet(t_env *e, uint32_t arg)
{
	*e->pos++ ^= (0xC0 + ((arg << 20) >> 26));
	*e->pos++ ^= (0x80 + ((arg << 26) >> 26));
	return (2);
}
