/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:24:06 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 17:50:35 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t		i;

	i = -1;
	while (src[++i] != '\0' && i < len)
		dst[i] = src[i];
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}
