/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:38:16 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/24 17:45:42 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*dst;

	if (!s)
		return (NULL);
	i = 0;
	if (!(dst = ft_strnew(len)))
		return (NULL);
	while (i < start)
	{
		s++;
		i++;
	}
	ft_strncpy(dst, s, len);
	return (dst);
}
