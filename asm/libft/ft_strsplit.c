/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:51:37 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		d;
	size_t		count_words;

	if (!s || !(tab =
		(char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	count_words = ft_count_words(s, c);
	while (i < count_words)
	{
		while (*s && *s == c)
			s++;
		d = 0;
		while (*(s + d) && *(s + d) != c)
			d++;
		if (!(ft_tabadd_sec(&tab, i, d)))
			return (NULL);
		tab[i] = ft_strncpy(tab[i], s, d);
		s += d;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
