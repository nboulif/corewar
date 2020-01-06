/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 18:57:30 by nsondag           #+#    #+#             */
/*   Updated: 2018/11/29 11:49:02 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	i = 1;
	if (ft_strcmp(needle, "") == 0)
		return ((char*)haystack);
	while (*haystack && i <= len - ft_strlen(needle) + 1 && len)
	{
		if (ft_strchr(haystack, (int)*needle))
		{
			if (ft_strncmp(needle, haystack, ft_strlen(needle)) == 0
					&& ft_strlen(needle) <= len)
				return ((char*)haystack);
		}
		haystack++;
		i++;
	}
	return (NULL);
}
