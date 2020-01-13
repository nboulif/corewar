/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:06:27 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/06 15:55:45 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		l;
	size_t		i;

	l = ft_strlen(dst);
	if (l + 1 > size)
		return (ft_strlen(src) + size);
	i = 0;
	while (l + i < size - 1 && src[i] != '\0')
	{
		dst[l + i] = src[i];
		++i;
	}
	dst[l + i] = '\0';
	return (l + ft_strlen(src));
}
