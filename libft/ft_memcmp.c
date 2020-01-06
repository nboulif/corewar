/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 15:18:21 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/24 19:37:44 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*sc1;
	unsigned char	*sc2;

	if (n == 0)
		return (0);
	i = 1;
	sc1 = (unsigned char*)s1;
	sc2 = (unsigned char*)s2;
	while (i < n && *sc1 == *sc2)
	{
		sc1++;
		sc2++;
		i++;
	}
	return (*sc1 - *sc2);
}
