/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:49:50 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t	ft_strlcat(char *dst, const char *src, uint32_t size)
{
	uint32_t		dst_len;
	uint32_t		src_len;
	uint32_t		i;
	uint32_t		j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = ft_strlen(dst);
	j = 0;
	if (!(size))
		return (src_len);
	while (*(src + j) && i < size - 1)
		*(dst + i++) = *(src + j++);
	size >= dst_len ? *(dst + i) = '\0' : 0;
	return (size < dst_len ? src_len + size : src_len + dst_len);
}
