/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:22:25 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/22 17:15:59 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char chr;

	chr = (char)c;
	while (*s)
	{
		if (*s == chr)
			return ((char*)s);
		s++;
	}
	if (chr == '\0')
		return ((char*)s);
	return (NULL);
}
