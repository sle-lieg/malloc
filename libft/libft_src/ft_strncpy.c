/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 22:33:47 by sle-lieg          #+#    #+#             */
/*   Updated: 2018/05/17 17:12:58 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;
	printf("len= %lu\n", len);

	i = 0;
	while (i < len)
	{
		if (!src[i])
		{
			while (i < len)
				dst[i++] = '\0';
		}
		else
		{
			dst[i] = src[i];
			i++;
		}
	}
	return (dst);
}
