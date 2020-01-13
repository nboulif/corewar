/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:07:35 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/06 16:14:06 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;
	size_t			l_haystack;
	size_t			l_needle;

	if (needle[0] == '\0')
		return ((char *)haystack);
	l_haystack = ft_strlen(haystack);
	l_haystack = (l_haystack < len) ? l_haystack : len;
	l_needle = ft_strlen(needle);
	i = 0;
	while (l_haystack - i >= l_needle)
	{
		j = 0;
		while (haystack[i + j] == needle[j])
			if (needle[++j] == '\0')
				return ((char *)haystack + i);
		++i;
	}
	return (NULL);
}
