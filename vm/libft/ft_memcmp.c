/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:46:23 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, uint32_t n)
{
	uint32_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && ((uint8_t*)s1)[i] == ((uint8_t*)s2)[i])
		i++;
	if (((uint8_t*)s1)[i] == ((uint8_t*)s2)[i])
		return (0);
	return (((uint8_t*)s1)[i] - ((uint8_t*)s2)[i]);
}
