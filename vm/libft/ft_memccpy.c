/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:46:09 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, uint32_t n)
{
	uint32_t	i;

	i = 0;
	while (i < n)
	{
		((uint8_t *)dst)[i] = ((uint8_t*)src)[i];
		if ((uint8_t)c == ((uint8_t*)src)[i])
			return (&((uint8_t*)dst)[++i]);
		i++;
	}
	return (NULL);
}
