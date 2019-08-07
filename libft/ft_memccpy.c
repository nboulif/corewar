/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:56:10 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/25 20:34:01 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dstc;
	unsigned char	*srcc;
	size_t			i;

	dstc = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*dstc = *srcc;
		if (*dstc == (unsigned char)c)
			return (dstc + 1);
		i++;
		dstc++;
		srcc++;
	}
	return (NULL);
}
