/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:39:47 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 13:23:17 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;

	if (dst < src)
		return (ft_memcpy(dst, src, len));
	d = (unsigned char *)dst;
	while (len > 0)
	{
		--len;
		*(d + len) = *((unsigned char *)src + len);
	}
	return (dst);
}
