/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:27:22 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/23 19:25:33 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dstc;
	char	*srcc;

	if (dst > src)
	{
		dstc = (char *)dst;
		srcc = (char *)src;
		while (len--)
			dstc[len] = srcc[len];
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
