/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:51:18 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	y;

	if (!(*needle))
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		y = 0;
		while (i + y < len && haystack[i + y] && needle[y]
			&& haystack[i + y] == needle[y])
			y++;
		if (needle[y] == '\0')
			return (&((char*)haystack)[i]);
		i++;
	}
	return (NULL);
}
