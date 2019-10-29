/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:21:34 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/24 16:05:26 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t size_dst;

	size_dst = ft_strlen(dst);
	if (size > size_dst)
	{
		dst = ft_strncat(dst, src, size - size_dst - 1);
		return (size_dst + ft_strlen(src));
	}
	else
		return (size + ft_strlen(src));
}
