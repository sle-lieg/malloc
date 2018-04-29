/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 02:48:42 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/03/10 01:42:54 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wchar_len(uint32_t car)
{
	if (car & FOUR)
		return (4);
	else if (car & THREE)
		return (3);
	else if (car & TWO)
		return (2);
	else if (car)
		return (1);
	return (0);
}
