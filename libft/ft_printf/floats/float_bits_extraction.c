/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_bits_extraction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:10:20 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:23:52 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	*uc_memcpy(unsigned char *dst, const void *src,
		size_t n)
{
	size_t			i;

	i = -1;
	while (++i < n)
		dst[i] = *((unsigned char*)src + i);
	return (dst);
}

static unsigned char	*uc_memmove(unsigned char *dst, const void *src,
		size_t n)
{
	if ((void*)dst < src)
		return (uc_memcpy(dst, src, n));
	while (n > 0)
	{
		--n;
		dst[n] = *((unsigned char *)src + n);
	}
	return (dst);
}

unsigned char			*store_ldouble_bits(long double in)
{
	unsigned char	*bits;

	bits = (unsigned char*)malloc(sizeof(in));
	if (!bits)
		return (NULL);
	bits = uc_memmove(bits, &in, sizeof(in));
	return (bits);
}

unsigned char			*store_double_bits(double in)
{
	unsigned char	*bits;

	bits = (unsigned char*)malloc(sizeof(in));
	if (!bits)
		return (NULL);
	bits = uc_memmove(bits, &in, sizeof(in));
	return (bits);
}
