/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:07:30 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/24 18:50:16 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dstc;

	dstc = (char *)dst;
	i = 0;
	while (i < n)
	{
		*dstc = *(char*)src;
		dstc++;
		src++;
		i++;
	}
	return (dstc - n);
}
