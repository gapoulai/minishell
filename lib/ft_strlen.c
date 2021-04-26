/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 00:14:27 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 17:43:48 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(char *str)
{
	char	*s;

	if (!str)
		return (0);
	s = str;
	while (*str)
		++str;
	return (str - s);
}
