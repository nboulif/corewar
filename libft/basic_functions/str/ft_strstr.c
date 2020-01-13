/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 18:17:33 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/06 15:58:04 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	size_t			i;
	size_t			j;
	size_t			l_haystack;
	size_t			l_needle;

	if (needle[0] == '\0')
		return ((char *)haystack);
	l_haystack = ft_strlen(haystack);
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
