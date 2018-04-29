/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:48:10 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/04/21 12:24:03 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int nb;
	int i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			nb++;
		i++;
	}
	return (nb);
}

static int	ft_size_word(const char *s, char c, int *j)
{
	int nb;

	nb = 0;
	while (s[*j] == c)
		(*j)++;
	while (s[*j] && s[*j] != c)
	{
		(*j)++;
		nb++;
	}
	return (nb);
}

static void	ft_fillarray(char **split, const char *s, char c, int nb_words)
{
	int i;
	int j;
	int nb_char;

	i = 0;
	j = 0;
	nb_char = 0;
	while (i < nb_words)
	{
		nb_char = ft_size_word(s, c, &j);
		if (!(split[i] = (char *)malloc(sizeof(**split) * (nb_char + 1))))
			exit(EXIT_FAILURE);
		split[i][nb_char] = '\0';
		ft_strncpy(split[i], s + (j - nb_char), nb_char);
		i++;
	}
}

char		**ft_strsplit(const char *s, char c)
{
	char	**split;
	int		nb_words;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s || c < 32 || c > 126)
		return (NULL);
	nb_words = ft_count_words(s, c);
	if (!(split = (char **)malloc(sizeof(*split) * (nb_words + 1))))
		exit(EXIT_FAILURE);
	split[nb_words] = NULL;
	ft_fillarray(split, s, c, nb_words);
	return (split);
}
