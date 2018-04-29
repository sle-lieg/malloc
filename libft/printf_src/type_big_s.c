/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_big_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 01:36:37 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/03/10 01:37:37 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_type_big_s(t_env *e)
{
	uint32_t *arg;

	arg = va_arg(e->ap, uint32_t*);
	if (!arg)
		e->accu = 6;
	else if (!e->accu_bool)
		e->accu = ft_wstr_len(arg);
	else
	{
		ft_get_accu(e, arg);
	}
	e->width -= e->accu;
	if (e->flags[MIN])
		ft_post_indent_big_s(e, arg);
	else
		ft_pre_indent_big_s(e, arg);
}

void	ft_get_accu(t_env *e, uint32_t *arg)
{
	int	tmp;
	int	len;

	len = 0;
	while ((tmp = ft_wchar_len(*arg++)))
	{
		if ((len + tmp) > e->accu)
		{
			e->accu = len;
			break ;
		}
		len += tmp;
	}
	if (len < e->accu)
		e->accu = len;
}

void	ft_fill_wstring(t_env *e, uint32_t *arg)
{
	while (e->accu > 0)
	{
		*(int *)e->pos = 0;
		if (*arg & FOUR)
			e->accu -= ft_four_octet(e, *arg);
		else if (*arg & THREE)
			e->accu -= ft_three_octet(e, *arg);
		else if (*arg & TWO)
			e->accu -= ft_two_octet(e, *arg);
		else if (*arg)
		{
			*e->pos++ = *arg;
			e->accu--;
		}
		arg++;
	}
}

void	ft_post_indent_big_s(t_env *e, uint32_t *arg)
{
	char *tmp;

	if (!arg)
	{
		tmp = "(null)";
		while (e->accu--)
			*e->pos++ = *tmp++;
	}
	else
		ft_fill_wstring(e, arg);
	while (e->width-- > 0)
		*e->pos++ = ' ';
}

void	ft_pre_indent_big_s(t_env *e, uint32_t *arg)
{
	char *tmp;

	while (e->width-- > 0)
		*e->pos++ = (e->flags[ZERO] ? '0' : ' ');
	if (!arg)
	{
		tmp = "(null)";
		while (e->accu--)
			*e->pos++ = *tmp++;
	}
	else
		ft_fill_wstring(e, arg);
}
