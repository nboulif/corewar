/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:14:22 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 18:31:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;

	i = 0;
	d = (unsigned char *)dst;
	while (i < n)
	{
		*(d + i) = *((unsigned char *)src + i);
		if (*((unsigned char *)src + i++) == (unsigned char)c)
			return (dst + i);
	}
	return (NULL);
}
