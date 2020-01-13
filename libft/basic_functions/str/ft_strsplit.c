/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:00:44 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 17:58:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strsplitsize(char const *s, char c)
{
	size_t		i;
	size_t		splitsize;

	splitsize = sizeof(char *);
	if (s == NULL)
		return (splitsize);
	i = -1;
	while (s[++i] == c)
		;
	while (s[i] != '\0')
	{
		if (s[i + 1] == '\0' || (s[i] == c && s[i + 1] != c))
			splitsize += sizeof(char *);
		i++;
	}
	return (splitsize);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**out;
	size_t		i;
	size_t		words;
	size_t		len_word;

	out = (s == NULL) ? NULL : (char **)ft_memalloc(ft_strsplitsize(s, c));
	i = 0;
	words = 0;
	while (out != NULL && s[i] != '\0')
	{
		while (s[i] == c)
			++i;
		len_word = 0;
		while (s[i + len_word] != c && s[i + len_word] != '\0')
			++len_word;
		if (len_word > 0 && !(out[words++] = ft_strsub2(s, i, len_word)))
			ft_strdel_ptr(&out);
		i += len_word;
	}
	if (out != NULL)
		out[words] = NULL;
	return (out);
}
