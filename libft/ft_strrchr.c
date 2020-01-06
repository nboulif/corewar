/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:22:25 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/24 19:33:06 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	int		i;

	i = 0;
	chr = (char)c;
	while (*s)
	{
		s++;
		i++;
	}
	if (c == 0)
		return ((char*)s);
	while (i >= 0)
	{
		if (*s == chr)
			return ((char*)s);
		s--;
		i--;
	}
	return (NULL);
}
