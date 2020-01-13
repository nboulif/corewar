/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 14:39:10 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 18:32:24 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;

	i = 0;
	d = (unsigned char *)dst;
	while (i < n)
	{
		*(d + i) = *((unsigned char *)src + i);
		++i;
	}
	return (dst);
}
