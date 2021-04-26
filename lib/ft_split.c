/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:55:25 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 19:13:42 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		words;
	int		check;

	i = 0;
	words = 0;
	while (s[i])
	{
		check = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			check = 1;
		}
		words += check;
	}
	return (words);
}

static int	get_word_length(char const *s, char c, int index)
{
	int		l;

	l = 0;
	while (s[index] && s[index] != c)
	{
		index++;
		l++;
	}
	return (l);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	if (!s)
		return (NULL);
	tab = gc_malloc(sizeof(char *) * (count_words(s, c) + 1));
	i = 0;
	k = 0;
	while (k < count_words(s, c))
	{
		j = 0;
		while (s[i] == c)
			i++;
		tab[k] = gc_malloc(sizeof(char) * (get_word_length(s, c, i) + 1));
		while (s[i] && s[i] != c)
			tab[k][j++] = s[i++];
		tab[k][j] = 0;
		k++;
	}
	tab[k] = NULL;
	return (tab);
}