/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:12:03 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/25 14:32:04 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sc;

	sc = (unsigned char *)s;
	i = 1;
	while (i <= n)
	{
		if (*sc == (unsigned char)c)
			return ((void*)sc);
		sc++;
		i++;
	}
	return (NULL);
}
