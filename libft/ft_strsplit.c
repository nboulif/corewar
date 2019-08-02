/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 21:03:45 by nsondag           #+#    #+#             */
/*   Updated: 2018/11/30 12:42:54 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(const char *s, char c)
{
	size_t len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		len++;
	}
	return (len);
}

static char		**free_tab(char **tab)
{
	int i;

	i = 0;
	while (i > 0)
		free(tab[--i - 1]);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**dst;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s || !(dst = (char**)malloc(sizeof(char*) * (word_count(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		j = 0;
		while (*s == c)
			s++;
		if (!*s)
			break ;
		len = word_len(s, c);
		if (!(dst[i] = ft_strnew(len)))
			return (free_tab(dst));
		while (j < len && *s)
			dst[i][j++] = *s++;
		i++;
	}
	dst[i] = NULL;
	return (dst);
}
